/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.


#pragma once

#include <system_error>


namespace tools {
namespace network {


struct PosixNetworkErrorCategory : std::error_category
{
     const char* name() const noexcept override;
     std::string message( int code ) const override;
};


const std::error_category& posixNetworkCategory();


} // namespace network
} // namespace tools
