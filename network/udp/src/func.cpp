///
/// func.cpp
///
/// Created on: Mar 12, 2017
///     Author: alexen
///

#include <network/udp/func.h>
#include <unistd.h>
#include <string.h>
#include <memory>


namespace tools {
namespace network {
namespace udp {


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


int socket( int pfamily, std::error_code& ec ) noexcept
{
     const auto sock = socket( pfamily, SOCK_DGRAM, 0 ) ;
     if( sock < 0 )
     {
          ec.assign( errno, std::system_category() );
     }
     return sock;
}


int socket( int pfamily ) throw( std::system_error )
{
     std::error_code ec;
     const auto sock = socket( pfamily, ec );
     if( ec )
     {
          throw std::system_error( ec, "create UDP socket" );
     }
     return sock;
}


Connection connect( const char* const hostname, int port, std::error_code& ec ) noexcept
{
     addrinfo* info = nullptr;
     const auto error = getaddrinfo( hostname, std::to_string( port ).c_str(), nullptr, &info );
     if( error )
     {
          ec.assign( error, std::system_category() );
          return Connection{};
     }

     std::unique_ptr< addrinfo, decltype( &freeaddrinfo ) > autocleaner( info, &freeaddrinfo );

     const auto sockfd = socket( info->ai_family, ec );
     if( ec )
     {
          return Connection{};
     }

     return Connection{ sockfd, info->ai_family, info->ai_addr, info->ai_addrlen };
}


Connection connect( const char* const hostname, int port ) throw( std::system_error )
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


int send( const Connection& c, const char* data, std::size_t datalen ) noexcept
{
     return sendto(
          c.sockfd,
          data,
          datalen,
          0,
          reinterpret_cast< const sockaddr* >( &c.addr.addr ),
          c.addr.addrlen );
}


int send( const Connection& c, const std::string& message ) noexcept
{
     return send( c, message.c_str(), message.size() );
}


int send( const char* const hostname, int port, const char* data, std::size_t datalen, std::error_code& ec ) noexcept
{
     const auto& c = connect( hostname, port, ec );
     if( ec )
     {
          return -1;
     }
     return send( c, data, datalen );
}


int send( const char* const hostname, int port, const std::string& message, std::error_code& ec ) noexcept
{
     return send( hostname, port, message.c_str(), message.size(), ec );
}


int send( const char* const hostname, int port, const char* data, std::size_t datalen ) throw( std::system_error )
{
     std::error_code ec;
     const auto& c = connect( hostname, port, ec );
     if( ec )
     {
          throw std::system_error( ec, "create UDP connection" );
     }
     return send( c, data, datalen );
}


int send( const char* const hostname, int port, const std::string& message ) throw( std::system_error )
{
     return send( hostname, port, message.c_str(), message.size() );
}


} // namespace udp
} // namespace network
} // namespace tools
