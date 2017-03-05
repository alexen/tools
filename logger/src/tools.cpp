///
/// tools.cpp
///
/// Created on: Mar 5, 2017
///     Author: alexen
///

#include <logger/tools.h>
#include <ostream>


namespace logger {
namespace tools {


void slice( const std::size_t chunkSize, const char* text, const std::size_t size,
     std::function< void( const char*, std::size_t ) >&& cb )
{
     const char* current = text;
     const char* const end = text + size;
     std::size_t bytes = 0;

     while( current != end )
     {
          bytes = std::min( chunkSize, static_cast< std::size_t >( end - current ) );
          cb( current, bytes );
          current += bytes;
     }
}


void slice( const std::size_t chunkSize, const std::string& text,
     std::function< void( const char*, std::size_t ) >&& cb )
{
     slice( chunkSize, text.c_str(), text.size(), std::move( cb ) );
}


void slice( const std::size_t chunkSize, const char* text, const std::size_t size, std::ostream& os )
{
     slice( chunkSize, text, size,
          [ &os ]( const char* ptr, std::size_t size )
          {
               os.write( ptr, size );
          }
     );
}


void slice( const std::size_t chunkSize, const std::string& text, std::ostream& os )
{
     slice( chunkSize, text.c_str(), text.size(), os );
}


} // namespace tools
} // namespace logger
