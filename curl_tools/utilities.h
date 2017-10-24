///
/// funcs.h
///
/// Created on: Sep 28, 2017
///     Author: alexen
///

#pragma once

#include <curl_tools/types.h>
#include <iosfwd>


namespace curl_tools {
namespace utilities {


types::CurlUptr makeCurl();


types::CurlHeadersListUptr makeHeadersList( types::Headers&& headers );


void updateHeadersList( types::CurlHeadersListUptr& existing, types::Headers&& headers );


void setBasicAuth(
     const types::CurlUptr& curl,
     const std::string& login,
     const std::string& password );


void setUserAgent( const types::CurlUptr& curl, const std::string& userAgent );


void setResponseHeadersOutput( const types::CurlUptr& curl, std::ostream& );


} // namespace utilities
} // namespace curl_tools
