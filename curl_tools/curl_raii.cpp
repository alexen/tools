///
/// curl_raii.cpp
///
/// Created on: Jun 21, 2017
///     Author: alexen
///

#include <curl_tools/curl_raii.h>

#include <stdexcept>
#include <utility>
#include <ostream>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>


namespace curl {
namespace tools {
namespace raii {


namespace {
namespace inner {


std::size_t toOstream( const char* const ptr, std::size_t size, std::size_t nmemb, void* userdata )
{
     std::ostream& ostr = *static_cast< std::ostream* >( userdata );
     const auto bytes = size * nmemb;
     ostr.write( ptr, bytes );
     return bytes;
}


} // namespace inner
} // namespace {unnamed}


CURL* CurlRaii::init()
{
     auto curl = curl_easy_init();
     if( !curl )
     {
          BOOST_THROW_EXCEPTION( std::runtime_error{ "curl init error" } );
     }
     return curl;
}


CurlRaii::CurlRaii()
     : curl_{ CurlRaii::init() }
{}


CurlRaii::CurlRaii( const std::string& url )
     : CurlRaii{}
{
     setUrl( url );
}


CurlRaii::~CurlRaii()
{
     curl_slist_free_all( slist_ );
     curl_easy_cleanup( curl_ );
     slist_ = nullptr;
     curl_ = nullptr;
}


CurlRaii& CurlRaii::setUrl( const std::string& url )
{
     setOpt( CURLOPT_URL, url.c_str() );
     return *this;
}


CurlRaii& CurlRaii::setHeaders( std::map< std::string, std::string >&& headers )
{
     curl_slist* slist = nullptr;
     for( auto&& item: headers )
     {
          slist = curl_slist_append( slist, (item.first + ": " + item.second).c_str() );
     }
     setOpt( CURLOPT_HTTPHEADER, slist );
     curl_slist_free_all( slist_ );
     slist_ = slist;
     return *this;
}


CurlRaii& CurlRaii::setResponseStream( std::ostream& ostr )
{
     setOpt( CURLOPT_WRITEFUNCTION, inner::toOstream );
     setOpt( CURLOPT_WRITEDATA, reinterpret_cast< void* >( std::addressof( ostr ) ) );
     return *this;
}



int CurlRaii::getHttpResponseStatus() const
{
     long status = 0;
     curl_easy_getinfo( curl_, CURLINFO_HTTP_CODE, &status );
     return static_cast< int >( status );
}



void CurlRaii::perform()
{
     CURLcode rc = CURLE_OK;
     perform( rc );
     if( rc != CURLE_OK )
     {
          BOOST_THROW_EXCEPTION(
               std::runtime_error{ "curl error: "
                    + std::string{ curl_easy_strerror( rc ) } } );
     }
}


void CurlRaii::perform( CURLcode& retCode ) noexcept
{
     retCode = curl_easy_perform( curl_ );
}


} // namespace raii
} // namespace tools
} // namespace curl
