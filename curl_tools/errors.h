///
/// errors.h
///
/// Created on: Oct 24, 2017
///     Author: alexen
///

#pragma once

#include <stdexcept>
#include <boost/exception/exception.hpp>
#include <curl/curl.h>


namespace curl_tools {
namespace errors {


struct CurlError : std::runtime_error, boost::exception {
     explicit CurlError( const std::string& what )
          : std::runtime_error{ what } {}
};

struct CurlRequestError : CurlError {
     explicit CurlRequestError( const CURLcode code )
          : CurlError{ curl_easy_strerror( code ) }, code{ code } {}
     const CURLcode code;
};


} // namespace errors
} // namespace curl_tools
