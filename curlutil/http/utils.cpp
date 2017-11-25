///
/// utilities.cpp
///
/// Created on: Sep 28, 2017
///     Author: alexen
///

#include <ostream>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <curlutil/base/data_writer.h>
#include <curlutil/base/utils.h>
#include <curlutil/http/errors.h>
#include <curlutil/http/utils.h>


namespace tools {
namespace curl {
namespace http {
namespace utils {


base::types::CurlSlistUptr makeHttpHeaders( types::Headers&& headers )
{
     auto slist = base::utils::makeSlist();
     extendHttpHeaders( slist, std::move( headers ) );
     return slist;
}


void extendHttpHeaders(
     base::types::CurlSlistUptr& slist,
     types::Headers&& headers
     )
{
     for( auto&& item: headers )
     {
          extendHttpHeaders( slist, item.first, item.second );
     }
}


void extendHttpHeaders(
     base::types::CurlSlistUptr& slist,
     const std::string& key,
     const std::string& value )
{
     auto item = key + ": " + value;
     base::utils::addSlistItem( slist, std::move( item ) );
}


void setBasicAuth(
     const base::types::CurlUptr& curl,
     const std::string& login,
     const std::string& password )
{
     curl_easy_setopt( curl.get(), CURLOPT_USERNAME, login.c_str() );
     curl_easy_setopt( curl.get(), CURLOPT_PASSWORD, password.c_str() );
}


void setUserAgent( const base::types::CurlUptr& curl, const std::string& userAgent )
{
     curl_easy_setopt( curl.get(), CURLOPT_USERAGENT, userAgent.c_str() );
}


void setResponseHeadersOutput( const base::types::CurlUptr& curl, std::ostream& ostr )
{
     curl_easy_setopt( curl.get(), CURLOPT_HEADERFUNCTION, base::data_writer::toOstream );
     curl_easy_setopt( curl.get(), CURLOPT_WRITEHEADER, &ostr );
}


}}}}
