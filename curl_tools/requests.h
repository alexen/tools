///
/// requests.h
///
/// Created on: Oct 24, 2017
///     Author: alexen
///

#pragma once

#include <curl_tools/types.h>
#include <cstddef>
#include <iosfwd>



namespace curl_tools {
namespace requests {


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


} // namespace requests
} // namespace curl_tools
