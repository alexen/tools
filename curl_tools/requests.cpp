///
/// requests.cpp
///
/// Created on: Oct 24, 2017
///     Author: alexen
///

#include <ostream>

#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <curl_tools/inner.h>
#include <curl_tools/requests.h>


namespace curl_tools {
namespace requests {


namespace {


static long request(
     const types::CurlUptr& curl,
     const types::CurlHeadersListUptr& headers,
     const std::string& url,
     const char* const data,
     std::size_t size,
     std::ostream& response )
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

     const auto ret = curl_easy_perform( curl.get() );
     if( ret != CURLE_OK )
     {
          BOOST_THROW_EXCEPTION( std::runtime_error{ curl_easy_strerror( ret ) } );
     }

     long httpStatus = 0;
     curl_easy_getinfo( curl.get(), CURLINFO_RESPONSE_CODE, &httpStatus );
     return httpStatus;
}


} // namespace {unnamed}


long get(
     const types::CurlUptr& curl,
     const types::CurlHeadersListUptr& headers,
     const std::string& url,
     std::ostream& response )
{
     return request( curl, headers, url, nullptr, 0, response );
}


long get(
     const types::CurlUptr& curl,
     const std::string& url,
     std::ostream& response )
{
     return get( curl, inner::consts::nullHeader, url, response );
}


long post(
     const types::CurlUptr& curl,
     const types::CurlHeadersListUptr& headers,
     const std::string& url,
     const char* const data,
     std::size_t size,
     std::ostream& response )
{
     return request( curl, headers, url, data, size, response );
}


long post(
     const types::CurlUptr& curl,
     const std::string& url,
     const char* const data,
     std::size_t size,
     std::ostream& response )
{
     return post( curl, inner::consts::nullHeader, url, data, size, response );
}


} // namespace requests
} // namespace curl_tools
