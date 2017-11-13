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
#include <tools/curl/base/utils.h>
#include <tools/curl/http/utils.h>
#include <tools/curl/http/requests.h>

static const std::string body = R"({
     "message": "My Bonny is over the ocean..."
})";


int main( /*int argc, char** argv*/ )
{
     using namespace tools::curl;

     try
     {
          const auto url = "http://127.0.0.1:9999";

          const auto curl = base::utils::makeCurl();

          std::cout << "Request:\n";

          auto headers =
               http::utils::makeHttpHeaders({
                    { "X-Extra-Header", "extra header value" }
               });

          http::utils::extendHttpHeaders( headers, {
               { "X-Another-Extra-Header", "some another extra value" }
          });

          http::utils::extendHttpHeaders( headers, {
               { "Content-Type", "application/json" }
          });

          http::utils::setBasicAuth( curl, "alexen", "111111" );
          http::utils::setUserAgent( curl, "Self-Written-Curl-Functions" );

          const auto status =
               http::requests::post(
                    curl,
                    headers,
                    url,
                    body.data(),
                    body.size(),
                    std::cout
                    );

          std::cout << "\nStatus: " << status << "\n";
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }
     return 0;
}
