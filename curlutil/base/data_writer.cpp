///
/// write_func.cpp
///
/// Created on: Nov 13, 2017
///     Author: alexen
///

#include <ostream>
#include <boost/assert.hpp>
#include <curlutil/base/data_writer.h>


namespace tools {
namespace curl {
namespace base {
namespace data_writer {


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
