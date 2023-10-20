///
/// tools.cpp
///
/// Created on: Mar 5, 2017
///     Author: alexen
///

#include <logging/tools.h>
#include <ostream>


namespace logger {
namespace tools {


void slice( const std::size_t chunkSize, std::string_view data, SliceHandler&& cb )
{
     auto curr = data.begin();
     const auto end = data.end();
     std::size_t bytes = 0;

     while( curr != end )
     {
          bytes = std::min( chunkSize, static_cast< std::size_t >( std::distance( curr, end ) ) );
          cb({ curr, bytes });
          std::advance( curr, bytes );
     }
}


void slice( const std::size_t chunkSize, std::string_view data, std::ostream& os )
{
     slice( chunkSize, data, [ &os ]( std::string_view chunk ) {
          os.write( chunk.data(), chunk.size() );
     });
}


} // namespace tools
} // namespace logger
