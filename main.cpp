///
/// main.cpp
///
/// Created on: Jun 20, 2017
///     Author: alexen
///

#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <boost/exception/diagnostic_information.hpp>

#include <curl/curl.h>


namespace curl {
namespace throw_exception {


void curlError( const std::string& message, const CURLcode code )
{
     throw std::runtime_error{ message + ": " + curl_easy_strerror( code ) };
}


} // namespace throw_exception


class Curl
{
public:
     Curl() : curl_{ std::move( Curl::init() ) } {}
     ~Curl()
     {
          curl_slist_free_all( slist_ );
          curl_easy_cleanup( curl_ );
     }

     template< typename T >
     Curl& setOpt( CURLoption option, T value )
     {
          curl_easy_setopt( curl_, option, value );
          return *this;
     }

     Curl& setHeaders( std::map< std::string, std::string >&& headers )
     {
          curl_slist_free_all( slist_ );
          for( auto&& item: headers )
          {
               slist_ = curl_slist_append( slist_, (item.first + ": " + item.second).c_str() );
          }
          curl_easy_setopt( curl_, CURLOPT_HTTPHEADER, slist_ );
          return *this;
     }

     void perform()
     {
          curl_easy_perform( curl_ );
     }

private:
     static CURL* init()
     {
          auto curl = curl_easy_init();
          if( !curl )
          {
               BOOST_THROW_EXCEPTION( std::runtime_error{ "curl init error" } );
          }
          return curl;
     }

     CURL* curl_ = nullptr;
     curl_slist* slist_ = nullptr;
};


} // namespace curl


int main()
{
     try
     {
          curl::Curl curl;
          curl.setOpt( CURLOPT_URL, "http://www.yandex.ru" )
               .setHeaders({
                    { "Authorization", "Basic klajhfalkfjhklasd" },
                    { "Content-Type", "plain/text" }
               })
               .perform();
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }

     return 0;
}
