/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#include <gtest/gtest.h>

#include <chrono>
#include <thread>
#include <random>

#include <stopwatch/stopwatch.h>


namespace {


std::random_device dev;
std::mt19937 gen( dev() );
std::uniform_int_distribution<> distr{ 50, 300 };


template< typename Duration >
Duration randomDuration()
{
     return Duration{ distr( gen ) };
}


} // namespace {unnamed}


TEST( Stopwatch, MeasureMicroseconds )
{
     using duration_t = std::chrono::microseconds;
     static const auto delay = randomDuration< duration_t >();
     tools::Stopwatch stopwatch;
     std::this_thread::sleep_for( delay );
     const auto elapsed = std::chrono::duration_cast< duration_t >( stopwatch.snapshot() );
     ASSERT_LE( delay.count(), elapsed.count() );
}


TEST( Stopwatch, MeasureMilliseconds )
{
     using duration_t = std::chrono::milliseconds;
     static const auto delay = randomDuration< duration_t >();
     tools::Stopwatch stopwatch;
     std::this_thread::sleep_for( delay );
     const auto elapsed = std::chrono::duration_cast< duration_t >( stopwatch.snapshot() );
     ASSERT_EQ( delay.count(), elapsed.count() );
}
