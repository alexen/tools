///
/// requests.cpp
///
/// Created on: Oct 24, 2017
///     Author: alexen
///

#include <tools/curl/http/requests.h>

#include <ostream>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <tools/curl/base/utils.h>
#include <tools/curl/base/write_func.h>
#include <tools/curl/http/errors.h>


namespace tools {
namespace curl {
namespace http {
namespace requests {


namespace {


static long getHttpStatus( const base::types::CurlUptr& curl )
{
     long httpStatus = 0;
     curl_easy_getinfo( curl.get(), CURLINFO_RESPONSE_CODE, &httpStatus );
     return httpStatus;
}


static long request(
     const base::types::CurlUptr& curl,
     const base::types::CurlSlistUptr& headers,
     const std::string& url,
     const char* const data,
     std::size_t size,
     std::ostream& response,
     const boost::optional< boost::posix_time::time_duration >& connectionTimeout,
     const boost::optional< boost::posix_time::time_duration >& requestTimeout
     )
{
     curl_easy_setopt( curl.get(), CURLOPT_URL, url.c_str() );
     if( data )
     {
          curl_easy_setopt( curl.get(), CURLOPT_POST, 1L );
          curl_easy_setopt( curl.get(), CURLOPT_POSTFIELDS, data );
          curl_easy_setopt( curl.get(), CURLOPT_POSTFIELDSIZE, size );
     }
     if( headers )
     {
          curl_easy_setopt( curl.get(), CURLOPT_HTTPHEADER, headers.get() );
     }
     curl_easy_setopt( curl.get(), CURLOPT_WRITEFUNCTION, base::write_funcs::toOstream );
     curl_easy_setopt( curl.get(), CURLOPT_WRITEDATA, &response );

     if( connectionTimeout )
     {
          base::utils::setConnectionTimeout( curl, *connectionTimeout );
     }
     if( requestTimeout )
     {
          base::utils::setRequestTimeout( curl, *requestTimeout );
     }

     const auto ret = curl_easy_perform( curl.get() );
     if( ret != CURLE_OK )
     {
          BOOST_THROW_EXCEPTION( errors::HttpRequestError{ ret } );
     }

     return getHttpStatus( curl );
}


} // namespace {unnamed}


long get(
     const base::types::CurlUptr& curl,
     const base::types::CurlSlistUptr& headers,
     const std::string& url,
     std::ostream& response,
     const boost::optional< boost::posix_time::time_duration >& connectionTimeout,
     const boost::optional< boost::posix_time::time_duration >& requestTimeout
     )
{
     return request( curl, headers, url, nullptr, 0, response, connectionTimeout, requestTimeout );
}


long get(
     const base::types::CurlUptr& curl,
     const std::string& url,
     std::ostream& response,
     const boost::optional< boost::posix_time::time_duration >& connectionTimeout,
     const boost::optional< boost::posix_time::time_duration >& requestTimeout
     )
{
     static base::types::CurlSlistUptr noHeaders{ nullptr, []( curl_slist* ){} };
     return get( curl, noHeaders, url, response, connectionTimeout, requestTimeout );
}


long post(
     const base::types::CurlUptr& curl,
     const base::types::CurlSlistUptr& headers,
     const std::string& url,
     const char* const data,
     std::size_t size,
     std::ostream& response,
     const boost::optional< boost::posix_time::time_duration >& connectionTimeout,
     const boost::optional< boost::posix_time::time_duration >& requestTimeout
     )
{
     return request( curl, headers, url, data, size, response, connectionTimeout, requestTimeout );
}


long post(
     const base::types::CurlUptr& curl,
     const std::string& url,
     const char* const data,
     std::size_t size,
     std::ostream& response,
     const boost::optional< boost::posix_time::time_duration >& connectionTimeout,
     const boost::optional< boost::posix_time::time_duration >& requestTimeout
     )
{
     static base::types::CurlSlistUptr noHeaders{ nullptr, []( curl_slist* ){} };
     return post( curl, noHeaders, url, data, size, response, connectionTimeout, requestTimeout );
}


}}}}
