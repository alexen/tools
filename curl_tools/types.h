///
/// types.h
///
/// Created on: Sep 28, 2017
///     Author: alexen
///

#pragma once

#include <map>
#include <string>
#include <memory>
#include <curl/curl.h>


namespace curl_tools {
namespace types {


using CurlUptr = std::unique_ptr< CURL, decltype( &curl_easy_cleanup ) >;
using CurlHeadersListUptr = std::unique_ptr< curl_slist, decltype( &curl_slist_free_all ) >;

using Headers = std::map< std::string, std::string >;


} // namespace types
} // namespace curl_tools
