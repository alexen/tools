///
/// utilities.cpp
///
/// Created on: Sep 28, 2017
///     Author: alexen
///

#include "utilities.h"
#include "errors.h"
#include "inner.h"

#include <ostream>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>


namespace curl_tools {
namespace utilities {


types::CurlUptr makeCurl()
{
     auto curl = curl_easy_init();
     if( !curl )
     {
          BOOST_THROW_EXCEPTION( errors::CurlError{ "curl init error" } );
     }
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


void setResponseHeadersOutput( const types::CurlUptr& curl, std::ostream& ostr )
{
     curl_easy_setopt( curl.get(), CURLOPT_HEADERFUNCTION, inner::toOstream );
     curl_easy_setopt( curl.get(), CURLOPT_WRITEHEADER, &ostr );
}


} // namespace utilities
} // namespace curl_tools
