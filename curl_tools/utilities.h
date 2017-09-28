///
/// funcs.h
///
/// Created on: Sep 28, 2017
///     Author: alexen
///

#pragma once

#include <iosfwd>
#include "types.h"


namespace curl {
namespace tools {
namespace utilities {


template< typename T >
T makeNull() = delete;


template<>
inline types::CurlUptr makeNull< types::CurlUptr >()
{
     return types::CurlUptr{ nullptr, []( CURL* ){} };
}


template<>
inline types::CurlHeadersListUptr makeNull< types::CurlHeadersListUptr >()
{
     return types::CurlHeadersListUptr{ nullptr, []( curl_slist* ){} };
}


types::CurlUptr makeCurl( bool verbose = false );


types::CurlHeadersListUptr makeHeadersList( types::Headers&& headers );


void updateHeadersList( types::CurlHeadersListUptr& existing, types::Headers&& headers );


void setBasicAuth(
     const types::CurlUptr& curl,
     const std::string& login,
     const std::string& password );


void setUserAgent( const types::CurlUptr& curl, const std::string& userAgent );


long get(
     const types::CurlUptr& curl,
     const types::CurlHeadersListUptr& headers,
     const std::string& url,
     std::ostream& response
     );


long get(
     const types::CurlUptr& curl,
     const std::string& url,
     std::ostream& response
     );


long post(
     const types::CurlUptr& curl,
     const types::CurlHeadersListUptr& headers,
     const std::string& url,
     const char* const data,
     std::size_t size,
     std::ostream& response
     );


long post(
     const types::CurlUptr& curl,
     const std::string& url,
     const char* const data,
     std::size_t size,
     std::ostream& response
     );


} // namespace utilities
} // namespace tools
} // namespace curl
