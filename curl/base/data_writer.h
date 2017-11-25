///
/// write_func.h
///
/// Created on: Nov 13, 2017
///     Author: alexen
///

#pragma once

#include <cstddef>


namespace tools {
namespace curl {
namespace base {
namespace data_writer {


std::size_t toOstream(
     const char* const ptr,
     const std::size_t size,
     const std::size_t nmemb,
     void* userdata
     );



}}}}
