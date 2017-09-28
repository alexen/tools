///
/// main.cpp
///
/// Created on: Jun 20, 2017
///     Author: alexen
///

#include <cstdio>
#include <list>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <boost/exception/diagnostic_information.hpp>

#include <curl_tools/utilities.h>


int main( int argc, char** argv )
{
     using namespace curl::tools;

     try
     {
          const auto url = "http://127.0.0.1:9999";

          const auto curl = utilities::makeCurl();

          std::cout << "Request:\n";

          auto headers =
               utilities::makeHeadersList({
                    { "X-Extra-Header", "extra header value" }
               });

          utilities::updateHeadersList( headers, {
               { "X-Another-Extra-Header", "some another extra value" }
          });

          const std::string body = ""
               "{\n"
               "\t\"message\": \"My Bonny is over the ocean...\"\n"
               "}\n";

          utilities::updateHeadersList( headers, {
               { "Content-Type", "application/json" }
          });

          utilities::setBasicAuth( curl, "alexen", "111111" );
          utilities::setUserAgent( curl, "Self-Writed-Curl-Functions" );

          const auto status = utilities::post(
               curl,
               headers,
               url,
               body.data(),
               body.size(),
               std::cout );

          std::cout << "\nStatus: " << status << "\n";
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }
     return 0;
}
