///
/// main.cpp
///
/// Created on: Mar 3, 2017
///     Author: alexen
///

#include <syslog.h>

#include <array>
#include <cerrno>
#include <set>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <system_error>

#include <boost/utility/string_view.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/optional.hpp>
#include <logging/syslog_ostreambuf.h>

#include <logging/syslogger.h>
#include <network/udp/utils.h>
#include <stopwatch/stopwatch.h>
#include <stopwatch/stopwatch_io.h>


int main()
{
     try
     {
          tools::logging::Ostreambuf osbuf{ "{PREFIX}" };
          std::ostream os{ &osbuf };

          os << "request from person bd78a58d-4b83-4460-a9ed-955ad69ddbfb "
               << "and company 3197f6b4-195a-435a-979e-7659d8603439:"
               "\n- name Ivanov Ivan Ivanovitch"
               "\n- birth date: 03.04.1963"
               "\n- certificate: 02:61:af:0d:f9:14"
               << std::endl;
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << "\n";
          return 1;
     }
     return 0;
}
