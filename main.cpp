///
/// main.cpp
///
/// Created on: Jun 20, 2017
///     Author: alexen
///

#include <stdexcept>
#include <iostream>
#include <boost/exception/diagnostic_information.hpp>


int main()
{
     try
     {

     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }

     return 0;
}
