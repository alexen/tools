///
/// utilities.cpp
///
/// Created on: Sep 28, 2017
///     Author: alexen
///

#include <ostream>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <curlutil/base/errors.h>
#include <curlutil/base/utils.h>


namespace tools {
namespace curl {
namespace base {
namespace utils {


types::CurlUptr makeCurl()
{
     auto curl = curl_easy_init();
     if( !curl )
     {
          BOOST_THROW_EXCEPTION( errors::CurlError{ "curl init error" } );
     }
     return types::CurlUptr{ curl, curl_easy_cleanup };
}


types::CurlSlistUptr makeSlist()
{
     return types::CurlSlistUptr{ nullptr, curl_slist_free_all };
}


void addSlistItem( types::CurlSlistUptr& slist, const char* const item )
{
     slist.reset( curl_slist_append( slist.release(), item ) );
}


void addSlistItem( types::CurlSlistUptr& slist, const std::string& item )
{
     addSlistItem( slist, item.c_str() );
}


void addSlistItem( types::CurlSlistUptr& slist, std::string&& item )
{
     addSlistItem( slist, item.c_str() );
}


void setPlainAuth(
     const types::CurlUptr& curl,
     const std::string& login,
     const std::string& password )
{
     curl_easy_setopt( curl.get(), CURLOPT_USERNAME, login.c_str() );
     curl_easy_setopt( curl.get(), CURLOPT_PASSWORD, password.c_str() );
}


void setConnectionTimeout(
     const types::CurlUptr& curl,
     const boost::posix_time::time_duration& timeout
     )
{
     curl_easy_setopt( curl.get(),  CURLOPT_CONNECTTIMEOUT, timeout.total_seconds() );
}


void setRequestTimeout(
     const types::CurlUptr& curl,
     const boost::posix_time::time_duration& timeout
     )
{
     curl_easy_setopt( curl.get(),  CURLOPT_TIMEOUT, timeout.total_seconds() );
}


}}}}
