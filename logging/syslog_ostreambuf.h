/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#pragma once

#include <array>
#include <streambuf>


namespace tools {
namespace logging {


class Ostreambuf : public std::streambuf
{
     using Base = std::streambuf;
public:
     ~Ostreambuf();
     explicit Ostreambuf( std::string&& prefix );
     Ostreambuf();

private:
     void resetBuffer();
     bool isBufferEmpty() const;
     int_type overflow( int_type c ) override;
     std::streamsize xsputn( const char* s, std::streamsize size ) override;
     int_type sync() override;

     std::string prefix_;
     std::array< char, 2048u > buffer_;
};


} // namespace logging
} // namespace tools
