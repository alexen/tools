///
/// stopwatch_io.h
///
/// Created on: Feb 27, 2017
///     Author: alexen
///

#pragma once

#include <iosfwd>
#include <chrono>


namespace tools {

class Stopwatch;

} // namespace tools


/// Оператора вывода в поток секундомера
///
/// Выводит в поток замер времени в трех видах: в секундах, миллисекундах и микросекундах
std::ostream& operator<<( std::ostream&, const std::chrono::system_clock::duration& );


/// Перегрузка для типа @p Stopwatch
///
/// Просто вызывает os << stopwatch.snapshot();
std::ostream& operator<<( std::ostream&, const tools::Stopwatch& );
