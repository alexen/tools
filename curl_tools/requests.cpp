///
/// requests.cpp
///
/// Created on: Oct 24, 2017
///     Author: alexen
///

#include "requests.h"
#include "errors.h"
#include "inner.h"
#include "utilities.h"

#include <ostream>

#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>


namespace curl_tools {
namespace requests {


namespace {


static long getHttpStatus( const types::CurlUptr& curl )
{
     long httpStatus = 0;
     curl_easy_getinfo( curl.get(), CURLINFO_RESPONSE_CODE, &httpStatus );
     return httpStatus;
}


static long request(
     const types::CurlUptr& curl,
     const types::CurlHeadersListUptr& headers,
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
     curl_easy_setopt( curl.get(), CURLOPT_WRITEFUNCTION, inner::toOstream );
     curl_easy_setopt( curl.get(), CURLOPT_WRITEDATA, &response );

     if( connectionTimeout )
     {
          utilities::setConnectionTimeout( curl, *connectionTimeout );
     }
     if( requestTimeout )
     {
          utilities::setRequestTimeout( curl, *requestTimeout );
     }

     const auto ret = curl_easy_perform( curl.get() );
     if( ret != CURLE_OK )
     {
          BOOST_THROW_EXCEPTION( errors::CurlRequestError{ ret } );
     }

     return getHttpStatus( curl );
}


} // namespace {unnamed}


long get(
     const types::CurlUptr& curl,
     const types::CurlHeadersListUptr& headers,
     const std::string& url,
     std::ostream& response,
     const boost::optional< boost::posix_time::time_duration >& connectionTimeout,
     const boost::optional< boost::posix_time::time_duration >& requestTimeout
     )
{
     return request( curl, headers, url, nullptr, 0, response, connectionTimeout, requestTimeout );
}


long get(
     const types::CurlUptr& curl,
     const std::string& url,
     std::ostream& response,
     const boost::optional< boost::posix_time::time_duration >& connectionTimeout,
     const boost::optional< boost::posix_time::time_duration >& requestTimeout
     )
{
     return get( curl, inner::consts::nullHeader, url, response, connectionTimeout, requestTimeout );
}


long post(
     const types::CurlUptr& curl,
     const types::CurlHeadersListUptr& headers,
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
     const types::CurlUptr& curl,
     const std::string& url,
     const char* const data,
     std::size_t size,
     std::ostream& response,
     const boost::optional< boost::posix_time::time_duration >& connectionTimeout,
     const boost::optional< boost::posix_time::time_duration >& requestTimeout
     )
{
     return post( curl, inner::consts::nullHeader, url, data, size, response, connectionTimeout, requestTimeout );
}


} // namespace requests
} // namespace curl_tools
