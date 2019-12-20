///
/// main.cpp
///
/// Created on: Mar 3, 2017
///     Author: alexen
///

#include <array>
#include <cerrno>
#include <set>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <system_error>
#include <vector>

#include <boost/utility/string_view.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/optional.hpp>
#include <boost/bind.hpp>

#include <logging/syslog_ostreambuf.h>
#include <logging/syslogger.h>
#include <network/udp/utils.h>
#include <curlutil/base/utils.h>
#include <stopwatch/stopwatch.h>
#include <stopwatch/stopwatch_io.h>


struct ToHexOutputFilter : public boost::iostreams::output_filter
{
     template< typename Sink >
     bool put( Sink& sink, unsigned char c )
     {
          static constexpr auto letters = "0123456789abcdef";
          return boost::iostreams::put( sink, letters[ c >> 4 ] )
               && boost::iostreams::put( sink, letters[ c & 0x0f ] );
     }
};


struct UrlEncoderFilter : boost::iostreams::multichar_output_filter
{
     explicit UrlEncoderFilter( const tools::curl::base::types::CurlUptr& curl )
          : curl_{ curl } {}

     template< typename Sink >
     std::streamsize write( Sink& sink, const char* s, std::streamsize size )
     {
          if( size > 0 )
          {
               const auto esc = tools::curl::base::utils::urlEscape( curl_, s, size );
               if( boost::iostreams::write( sink, esc.data(), esc.size() ) < 0 )
               {
                    return -1;
               }
          }
          return size;
     }

private:
     const tools::curl::base::types::CurlUptr& curl_;
};


void testFilter()
{
     boost::iostreams::filtering_ostream os;
     os.push( ToHexOutputFilter{} );
     os.push( std::cout );
     static constexpr unsigned char buff[] = {
          0x22, 0xf0, 0xdb, 0x74, 0xcf, 0x34, 0x5f, 0x0c, 0x1d, 0xc3, 0xb7, 0xca,
          0xf5, 0x4a, 0xc7, 0xce, 0x10, 0xb5, 0xb5, 0x46, 0x44, 0x5c, 0x6e, 0xc3,
          0x2f, 0x15, 0x84, 0x53, 0x21, 0x56, 0x21, 0xb0
     };
     os.write( reinterpret_cast< const char* >( &buff[ 0 ] ), sizeof( buff ) );
}


int main()
{
     try
     {
          tools::logging::Ostreambuf osbuf{ "{PREFIX}" };
          std::ostream os{ &osbuf };

          os << "request from person bd78a58d-4b83-4460-a9ed-955ad69ddbfb "
               << "and company 3197f6b4-195a-435a-979e-7659d8603439:"
               "\n- name Ivanov Ivan Ivanovitch"
               "\n- birth date: 03.04.1963"
               "\n- certificate: 02:61:af:0d:f9:14"
               << std::endl;
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << "\n";
          return 1;
     }
     return 0;
}
