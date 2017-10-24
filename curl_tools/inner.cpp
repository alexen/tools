///
/// inner.cpp
///
/// Created on: Oct 24, 2017
///     Author: alexen
///

#include <boost/assert.hpp>
#include <curl_tools/inner.h>
#include <ostream>


namespace curl_tools {
namespace inner {


namespace {


class CurlGlobalInitializer {
public:
     CurlGlobalInitializer()
     {
          curl_global_init( CURL_GLOBAL_ALL );
     }

     ~CurlGlobalInitializer()
     {
          curl_global_cleanup();
     }
};


CurlGlobalInitializer curlGlobalInitializer;


} // namespace {unnamed}


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


} // namespace inner
} // namespace curl_tools
