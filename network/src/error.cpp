/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#include <network/error.h>
#include <netdb.h>


namespace tools {
namespace network {


const char* PosixNetworkErrorCategory::name() const noexcept
{
     return "posix.network";
}


std::string PosixNetworkErrorCategory::message( const int code ) const
{
     return gai_strerror( code );
}


const std::error_category& posixNetworkCategory()
{
     static const PosixNetworkErrorCategory instance;
     return instance;
}


} // namespace network
} // namespace tools
