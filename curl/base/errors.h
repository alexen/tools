///
/// errors.h
///
/// Created on: Oct 24, 2017
///     Author: alexen
///

#pragma once

#include <string>
#include <stdexcept>
#include <boost/exception/exception.hpp>
#include <curl/curl.h>


namespace tools {
namespace curl {
namespace base {
namespace errors {


inline std::string makeErrorString( const CURLcode code )
{
     return curl_easy_strerror( code );
}


inline std::string buildErrorString( const CURLcode code, std::string&& what )
{
     what += ": ";
     what += makeErrorString( code );
     return what;
}


struct CurlError : std::runtime_error, boost::exception {
     explicit
     CurlError( const std::string& what )
          : std::runtime_error{ what } {}

     explicit
     CurlError( const CURLcode code )
          : CurlError{ makeErrorString( code ) } {}

     CurlError( const CURLcode code, std::string&& what )
          : CurlError{ buildErrorString( code, std::move( what ) ) } {}
};


}}}}
