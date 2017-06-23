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


int main( int argc, char** argv )
{
     try
     {
          const auto url = argc > 1 ? argv[ 1 ] : "www.yandex.ru";

          curl::tools::raii::CurlRaii{ url }
               .setResponseStream( std::cout )
               .perform();
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }
     return 0;
}
