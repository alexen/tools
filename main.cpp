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

#include <curl_tools/curl_raii.h>


int main()
{
     try
     {
          curl::tools::raii::CurlRaii curlRaii;
          curlRaii
               .setOpt( CURLOPT_URL, "www.yandex.ru" )
               .setHeaders({
                    { "Authorization",  "Basic JKhliUGHKYGkjhgk" },
                    { "Content-Type",   "plain/text" }
               })
               .perform();

          curlRaii
               .setHeaders({
                    { "Authorization",  "Bearer GDHHHHHHHHHHGDKJJJJJJJJJJJJJJHEGYYYYYYYYYYYYY" },
                    { "Content-Type",   "json" },
                    { "Content-Length", "234" }
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
