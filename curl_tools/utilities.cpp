///
/// utilities.cpp
///
/// Created on: Sep 28, 2017
///     Author: alexen
///

#include "utilities.h"

#include <ostream>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>


namespace curl {
namespace tools {
namespace utilities {


namespace {
namespace inner {


static std::size_t responseToOstream(
     const char* const ptr,
     const std::size_t size,
     const std::size_t nmemb,
     void* userdata )
{
     BOOST_ASSERT( static_cast< std::ostream* >( userdata ) != nullptr );
     std::ostream& ostr = *static_cast< std::ostream* >( userdata );
     const auto bytes = size * nmemb;
     ostr.write( ptr, bytes );
     return bytes;
}


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
     curl_easy_setopt( curl.get(), CURLOPT_WRITEFUNCTION, responseToOstream );
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


} // namespace inner
} // namespace {unnamed}


types::CurlUptr makeCurl( bool verbose )
{
     auto curl = curl_easy_init();
     if( !curl )
     {
          BOOST_THROW_EXCEPTION( std::runtime_error{ "curl init error" } );
     }
     curl_easy_setopt( curl, CURLOPT_VERBOSE, static_cast< long >( verbose ) );
     return types::CurlUptr{ curl, curl_easy_cleanup };
}


types::CurlHeadersListUptr makeHeadersList( types::Headers&& headers )
{
     types::CurlHeadersListUptr newHeadersList{ nullptr, curl_slist_free_all };
     updateHeadersList( newHeadersList, std::move( headers ) );
     return newHeadersList;
}


void updateHeadersList( types::CurlHeadersListUptr& headersList, types::Headers&& headers )
{
     for( auto&& item: headers )
     {
          const auto& value = item.first + ": " + item.second;
          headersList.reset( curl_slist_append( headersList.release(), value.c_str() ) );
     }
}


void setBasicAuth(
     const types::CurlUptr& curl,
     const std::string& login,
     const std::string& password )
{
     curl_easy_setopt( curl.get(), CURLOPT_USERNAME, login.c_str() );
     curl_easy_setopt( curl.get(), CURLOPT_PASSWORD, password.c_str() );
}


void setUserAgent( const types::CurlUptr& curl, const std::string& userAgent )
{
     curl_easy_setopt( curl.get(), CURLOPT_USERAGENT, userAgent.c_str() );
}


long get(
     const types::CurlUptr& curl,
     const types::CurlHeadersListUptr& headers,
     const std::string& url,
     std::ostream& response )
{
     return inner::request( curl, headers, url, nullptr, 0, response );
}


long get(
     const types::CurlUptr& curl,
     const std::string& url,
     std::ostream& response )
{
     return get( curl, makeNull< types::CurlHeadersListUptr >(), url, response );
}


long post(
     const types::CurlUptr& curl,
     const types::CurlHeadersListUptr& headers,
     const std::string& url,
     const char* const data,
     std::size_t size,
     std::ostream& response )
{
     return inner::request( curl, headers, url, data, size, response );
}


long post(
     const types::CurlUptr& curl,
     const std::string& url,
     const char* const data,
     std::size_t size,
     std::ostream& response )
{
     return post( curl, makeNull< types::CurlHeadersListUptr >(), url, data, size, response );
}


} // namespace utilities
} // namespace tools
} // namespace curl
