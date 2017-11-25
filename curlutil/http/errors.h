///
/// errors.h
///
/// Created on: Oct 24, 2017
///     Author: alexen
///

#pragma once

#include <curlutil/base/errors.h>


namespace tools {
namespace curl {
namespace http {
namespace errors {


struct HttpRequestError : base::errors::CurlError {
     explicit HttpRequestError( const std::string& what ) : base::errors::CurlError{ what } {}
     explicit HttpRequestError( const CURLcode code ) : base::errors::CurlError{ code } {}
     HttpRequestError( const CURLcode code, std::string&& what )
          : base::errors::CurlError{ code, std::move( what ) } {}
};


}}}}
