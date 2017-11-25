///
/// smart_ptr.h
///
/// Created on: Nov 13, 2017
///     Author: alexen
///

#pragma once

#include <memory>
#include <curl/curl.h>


namespace tools {
namespace curl {
namespace base {
namespace types {


using CurlUptr = std::unique_ptr< CURL, decltype( &curl_easy_cleanup ) >;
using CurlSlistUptr = std::unique_ptr< curl_slist, decltype( &curl_slist_free_all ) >;


}}}}
