///
/// func.cpp
///
/// Created on: Mar 12, 2017
///     Author: alexen
///

#include <network/udp/utils.h>

#include <unistd.h>
#include <string.h>
#include <memory>

#include <network/error.h>


namespace tools {
namespace network {
namespace udp {


namespace {
namespace inner {


static int socket( int pfamily, std::error_code& ec ) noexcept
{
     const auto sock = socket( pfamily, SOCK_DGRAM, 0 ) ;
     if( sock < 0 )
     {
          ec.assign( errno, std::system_category() );
     }
     return sock;
}


} // namespace inner
} // namespace {unnamed}


Connection::UniversalSockaddr::UniversalSockaddr() noexcept
{
     memset( &addr, 0, sizeof( addr ) );
}


Connection::UniversalSockaddr::UniversalSockaddr( const sockaddr* sa, socklen_t salen ) noexcept
     : addrlen( salen )
{
     memcpy( &addr, sa, salen );
}


Connection::Connection( int sfd, int fam, const sockaddr* sa, socklen_t salen ) noexcept
     : sockfd( sfd ), family( fam ), addr( sa, salen )
{}


Connection::~Connection()
{
     if( sockfd > 0 )
     {
          close( sockfd );
     }
}


Connection connect( const char* const hostname, int port, std::error_code& ec ) noexcept
{
     addrinfo* info = nullptr;
     const auto error = getaddrinfo( hostname, std::to_string( port ).c_str(), nullptr, &info );
     if( error )
     {
          ec.assign( error, posixNetworkCategory() );
          return Connection{};
     }

     std::unique_ptr< addrinfo, decltype( &freeaddrinfo ) > autocleaner( info, &freeaddrinfo );

     const auto sockfd = inner::socket( info->ai_family, ec );
     if( ec )
     {
          return Connection{};
     }

     return Connection{ sockfd, info->ai_family, info->ai_addr, info->ai_addrlen };
}


Connection connect( const char* const hostname, int port )
{
     std::error_code ec;

     /// @attention В данной функции нельзя объявлять переменную как константную ссылку,
     /// т.к. при возвращении объекта из функции осуществляется (ненужное!) копирование объекта
     /// с последующим вызовом деструктора, в котором осуществляется закрытие дескриптора!
     const auto c = connect( hostname, port, ec );
     if( ec )
     {
          throw std::system_error( ec, "create UDP connection" );
     }
     return c;
}


std::size_t send( const Connection& c, const char* data, std::size_t datalen, std::error_code& ec ) noexcept
{
     const auto bytes = sendto(
          c.sockfd,
          data,
          datalen,
          0,
          reinterpret_cast< const sockaddr* >( &c.addr.addr ),
          c.addr.addrlen
          );
     if( bytes < 0 )
     {
          ec.assign( errno, std::system_category() );
     }
     return static_cast< std::size_t >( bytes );
}


std::size_t send( const Connection& c, const std::string& message, std::error_code& ec ) noexcept
{
     return send( c, message.data(), message.size(), ec );
}


std::size_t send( const Connection& c, const char* data, std::size_t datalen )
{
     std::error_code ec;
     const auto bytes = send( c, data, datalen, ec );
     if( ec )
     {
          throw std::system_error{ ec, "sending via UDP" };
     }
     return bytes;
}


std::size_t send( const Connection& c, const std::string& message )
{
     return send( c, message.c_str(), message.size() );
}


std::size_t send( const char* const hostname, int port, const char* data, std::size_t datalen, std::error_code& ec ) noexcept
{
     const auto c = connect( hostname, port, ec );
     if( ec )
     {
          return static_cast< std::size_t >( -1 );
     }
     return send( c, data, datalen, ec );
}


std::size_t send( const char* const hostname, int port, const std::string& message, std::error_code& ec ) noexcept
{
     return send( hostname, port, message.data(), message.size(), ec );
}


std::size_t send( const char* const hostname, int port, const char* data, std::size_t datalen )
{
     return send( connect( hostname, port ), data, datalen );
}


std::size_t send( const char* const hostname, int port, const std::string& message )
{
     return send( hostname, port, message.data(), message.size() );
}


} // namespace udp
} // namespace network
} // namespace tools
