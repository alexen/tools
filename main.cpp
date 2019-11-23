///
/// main.cpp
///
/// Created on: Mar 3, 2017
///     Author: alexen
///

#include <cerrno>
#include <set>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <system_error>

#include <boost/utility/string_ref.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include <logger/syslogger.h>
#include <network/udp/utils.h>
#include <stopwatch/stopwatch.h>
#include <stopwatch/stopwatch_io.h>


void measureSend( const unsigned count, const char* const host, int port, const std::string& message )
{
     tools::Stopwatch stopwatch;
     unsigned success = 0;
     unsigned unknown = 0;
     unsigned failed = 0;
     std::set< int > errors;
     for( unsigned i = 0; i < count; ++i )
     {
          const auto n = tools::network::udp::send( host, port, message );
          if( n > 0 )
          {
               ++success;
          }
          else if( n == 0 )
          {
               ++unknown;
          }
          else
          {
               ++failed;
               errors.insert( errno );
          }
     }
     std::cout << "Sending " << count << " messages to " << host << " and port " << port << " took " << stopwatch << "\n";
     std::cout << "\tstat: success: " << success << ", failed: " << failed << ", unknown: " << unknown << "\n";
     for( const auto err: errors )
     {
          std::cout << "\t" << std::system_category().message( err ) << "\n";
     }
}


void measureSend( const unsigned count, const tools::network::udp::Connection& c, const std::string& message )
{
     tools::Stopwatch stopwatch;
     unsigned success = 0;
     unsigned unknown = 0;
     unsigned failed = 0;
     std::set< int > errors;
     for( unsigned i = 0; i < count; ++i )
     {
          const auto n = tools::network::udp::send( c, message );
          if( n > 0 )
          {
               ++success;
          }
          else if( n == 0 )
          {
               ++unknown;
          }
          else
          {
               ++failed;
               errors.insert( errno );
          }
     }
     std::cout << "Sending " << count << " messages to existing connection took " << stopwatch << "\n";
     std::cout << "\tstat: success: " << success << ", failed: " << failed << ", unknown: " << unknown << "\n";
     for( const auto err: errors )
     {
          std::cout << "\t" << std::system_category().message( err ) << "\n";
     }
}


void measureConnect( const unsigned count, const char* const host, int port )
{
     tools::Stopwatch stopwatch;
     for( unsigned i = 0; i < count; ++i )
     {
          tools::network::udp::connect( host, port );
     }
     std::cout << "Connected " << count << " times to " << host << " and port " << port << " took " << stopwatch << "\n";
}


int main()
{
     try
     {
          const auto hostIpV4 = "127.0.0.1";
          const auto hostIpV6 = "0:0:0:0:0:ffff:7f00:0001";
          const auto hostByName = "localhost";
          const int port = 9999;
          const std::string message = "This is a test message!";
          const auto messagesCount = 10000u;

          measureConnect( messagesCount, hostIpV4, port );
          measureConnect( messagesCount, hostIpV6, port );
          measureConnect( messagesCount, hostByName, port );

          measureSend( messagesCount, hostByName, port, message );
          measureSend( messagesCount, hostIpV6, port, message );
          measureSend( messagesCount, hostIpV4, port, message );

          measureSend( messagesCount, tools::network::udp::connect( hostIpV4, port ), message );
          measureSend( messagesCount, tools::network::udp::connect( hostIpV6, port ), message );
          measureSend( messagesCount, tools::network::udp::connect( hostByName, port ), message );
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << "\n";
          return 1;
     }
     return 0;
}
