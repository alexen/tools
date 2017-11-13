///
/// write_func.cpp
///
/// Created on: Nov 13, 2017
///     Author: alexen
///

#include <tools/curl/base/write_func.h>

#include <ostream>
#include <boost/assert.hpp>


namespace tools {
namespace curl {
namespace base {
namespace write_funcs {


std::size_t toOstream(
     const char* const ptr,
     const std::size_t size,
     const std::size_t nmemb,
     void* userdata )
{
     BOOST_ASSERT( static_cast< std::ostream* >( userdata ) != nullptr );
     std::ostream& ostr = *static_cast< std::ostream* >( userdata );
     const auto bytes = size * nmemb;
     ostr.write( ptr, bytes );
     return bytes;
}


}}}}
