/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#include <cstring>
#include <gtest/gtest.h>
#include <network/udp/utils.h>


namespace {
namespace aux {


static constexpr auto hostname = "localhost";
static constexpr auto port = 19999;


namespace ipv4 {


static constexpr auto localhost = "127.0.0.1";


} // namespace ipv4
namespace ipv6 {


static constexpr auto localhost = "0:0:0:0:0:ffff:7f00:1";


} // namespace ipv6
} // namespace aux
} // namespace {unnamed}



TEST( NetworkUdp, ConnectionToBadHostCausesException )
{
     static constexpr auto nonExistingAddress = "17409e99-f8af-4cdb-9c8d-529180e9b04e";
     static constexpr auto nonExistingPort = 12345;
     ASSERT_THROW( tools::network::udp::connect( nonExistingAddress, nonExistingPort ), std::system_error );
}


TEST( NetworkUdp, ConnectionToBadPortCausesException )
{
     static constexpr auto nonExistingPort = -1;
     ASSERT_THROW( tools::network::udp::connect( aux::hostname, nonExistingPort ), std::system_error );
}


TEST( NetworkUdp, ConnectionToBadHostSetsErrorCode )
{
     static constexpr auto nonExistingAddress = "17409e99-f8af-4cdb-9c8d-529180e9b04e";
     static constexpr auto nonExistingPort = 12345;
     std::error_code error;
     ASSERT_NO_THROW( tools::network::udp::connect( nonExistingAddress, nonExistingPort, error ) );
     ASSERT_TRUE( error );
     ASSERT_EQ( EAI_NONAME, error.value() );
     ASSERT_EQ( gai_strerror( EAI_NONAME ), error.message() );
}


TEST( NetworkUdp, ConnectionToBadPortSetsErrorCode )
{
     static constexpr auto nonExistingPort = -1;
     std::error_code error;
     ASSERT_NO_THROW( tools::network::udp::connect( aux::hostname, nonExistingPort, error ) );
     ASSERT_TRUE( error );
     ASSERT_EQ( EAI_SERVICE, error.value() );
     ASSERT_EQ( gai_strerror( EAI_SERVICE ), error.message() );
}


TEST( NetworkUdp, ValidConnectionToIpV4 )
{
     ASSERT_NO_THROW( tools::network::udp::connect( aux::ipv4::localhost, aux::port ) );
}


TEST( NetworkUdp, ValidConnectionToIpV6 )
{
     ASSERT_NO_THROW( tools::network::udp::connect( aux::ipv6::localhost, aux::port ) );
}
