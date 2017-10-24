///
/// inner.h
///
/// Created on: Oct 24, 2017
///     Author: alexen
///

#pragma once

#include "types.h"


namespace curl_tools {
namespace inner {
namespace consts {


const types::CurlHeadersListUptr nullHeader{ nullptr, []( curl_slist* ){} };


} // namespace consts


std::size_t toOstream(
     const char* const ptr,
     const std::size_t size,
     const std::size_t nmemb,
     void* userdata
     );


} // namespace inner
} // namespace curl_tools
