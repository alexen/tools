///
/// func.h
///
/// Created on: Mar 12, 2017
///     Author: alexen
///

#pragma once

#include <system_error>


namespace tools {
namespace network {
namespace udp {


struct Connection;


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
