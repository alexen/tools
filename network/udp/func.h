///
/// func.h
///
/// Created on: Mar 12, 2017
///     Author: alexen
///

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <system_error>


namespace tools {
namespace network {
namespace udp {


struct Connection
{
private:
     struct UniversalSockaddr
     {
          UniversalSockaddr() {}
          UniversalSockaddr( const sockaddr* sa, socklen_t salen );

          const socklen_t addrlen = 0;
          union {
               sockaddr_in sa;
               sockaddr_in6 sa6;
          }
          addr;
     };

public:
     Connection() {}
     Connection( int sfd, int fam, const sockaddr* sa, socklen_t salen );

     ~Connection();

     const int sockfd = 0;
     const int family = 0;
     const UniversalSockaddr addr;
};


Connection connect( const char* const hostname, int port, std::error_code& ec ) noexcept;
Connection connect( const char* const hostname, int port ) throw( std::system_error );

int send( const Connection& c, const char* data, std::size_t datalen ) noexcept;
int send( const Connection& c, const std::string& message ) noexcept;
int send( const char* const hostname, int port, const char* data, std::size_t datalen, std::error_code& ec ) noexcept;
int send( const char* const hostname, int port, const std::string& message, std::error_code& ec ) noexcept;
int send( const char* const hostname, int port, const char* data, std::size_t datalen ) throw( std::system_error );
int send( const char* const hostname, int port, const std::string& message ) throw( std::system_error );


} // namespace udp
} // namespace network
} // namespace tools
