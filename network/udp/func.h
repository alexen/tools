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


} // namespace udp
} // namespace network
} // namespace tools
