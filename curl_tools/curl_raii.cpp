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
     : curl_{ CurlRaii::init() }
{}


CurlRaii::~CurlRaii()
{
     curl_slist_free_all( slist_ );
     curl_easy_cleanup( curl_ );
     slist_ = nullptr;
     curl_ = nullptr;
}


CurlRaii& CurlRaii::setHeaders( std::map< std::string, std::string >&& headers )
{
     resetSlist();


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


{
}


} // namespace raii
} // namespace tools
} // namespace curl
