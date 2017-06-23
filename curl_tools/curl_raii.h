///
/// curl_raii.h
///
/// Created on: Jun 21, 2017
///     Author: alexen
///

#pragma once

#include <map>
#include <curl/curl.h>


namespace curl {
namespace tools {
namespace raii {


class CurlRaii
{
public:
     CurlRaii();
     ~CurlRaii();

     template< typename T >
     CurlRaii& setOpt( CURLoption option, T value )
     {
          curl_easy_setopt( curl_, option, value );
          return *this;
     }

     CurlRaii& setHeaders( std::map< std::string, std::string >&& headers );

     void perform();

private:
     static CURL* init();

     CURL* curl_ = nullptr;
     curl_slist* slist_ = nullptr;
};

} // namespace raii
} // namespace tools
} // namespace curl
