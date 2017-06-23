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
     explicit CurlRaii( const std::string& url );
     ~CurlRaii();

     template< typename T >
     CurlRaii& setOpt( CURLoption option, T value )
     {
          curl_easy_setopt( curl_, option, value );
          return *this;
     }

     CurlRaii& setUrl( const std::string& url );
     CurlRaii& setHeaders( std::map< std::string, std::string >&& headers );
     CurlRaii& setResponseStream( std::ostream& );

     int getHttpResponseStatus() const;

     void perform();

     void perform( CURLcode& retCode ) noexcept;

     CURL* native()
     {
          return curl_;
     }

private:
     static CURL* init();

     CURL* curl_ = nullptr;
     curl_slist* slist_ = nullptr;
};

} // namespace raii
} // namespace tools
} // namespace curl
