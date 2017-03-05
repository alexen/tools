///
/// stopwatch.cpp
///
/// Created on: Feb 27, 2017
///     Author: alexen
///

#include <stopwatch/stopwatch.h>


namespace tools {


Stopwatch::Stopwatch()
{
     restart();
}


void Stopwatch::restart()
{
     start_ = std::chrono::high_resolution_clock::now();
}


std::chrono::system_clock::duration Stopwatch::snapshot() const
{
     return std::chrono::high_resolution_clock::now() - start_;
}


} // namespace tools
