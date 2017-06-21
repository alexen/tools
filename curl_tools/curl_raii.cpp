///
/// curl_raii.cpp
///
/// Created on: Jun 21, 2017
///     Author: alexen
///

#include <curl_tools/curl_raii.h>

#include <stdexcept>
#include <algorithm>
#include <boost/throw_exception.hpp>


namespace curl {
namespace tools {
namespace raii {


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
     : curl_{ std::move( CurlRaii::init() ) }
{}


CurlRaii::~CurlRaii()
{
     resetSlist();
     resetCurl();
}


CurlRaii& CurlRaii::setHeaders( std::map< std::string, std::string >&& headers )
{
     resetSlist();

     for( auto&& item: headers )
     {
          slist_ = curl_slist_append( slist_, (item.first + ": " + item.second).c_str() );
     }
     curl_easy_setopt( curl_, CURLOPT_HTTPHEADER, slist_ );
     return *this;
}


void CurlRaii::perform()
{
     const auto rc = curl_easy_perform( curl_ );
     if( rc != CURLE_OK )
     {
          BOOST_THROW_EXCEPTION(
               std::runtime_error{ "curl error: "
                    + std::string{ curl_easy_strerror( rc ) } } );
     }
}


void CurlRaii::resetSlist() noexcept
{
     curl_slist_free_all( slist_ );
     slist_ = nullptr;
}


void CurlRaii::resetCurl() noexcept
{
     curl_easy_cleanup( curl_ );
     curl_ = nullptr;
}


} // namespace raii
} // namespace tools
} // namespace curl
