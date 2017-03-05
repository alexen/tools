///
/// stopwatch.cpp
///
/// Created on: Feb 27, 2017
///     Author: alexen
///

#include <stopwatch/stopwatch_io.h>
#include <chrono>
#include <ostream>
#include <stopwatch/stopwatch.h>


std::ostream& operator<<( std::ostream& os, const std::chrono::system_clock::duration& dur )
{
     os << std::chrono::duration< double >( dur ).count() << " s ("
          << std::chrono::duration_cast< std::chrono::milliseconds >( dur ).count() << " ms, "
          << std::chrono::duration_cast< std::chrono::microseconds >( dur ).count() << " us)";
     return os;
}


std::ostream& operator<<( std::ostream& os, const tools::Stopwatch& stopwatch )
{
     os << stopwatch.snapshot();
     return os;
}
