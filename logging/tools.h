///
/// tools.h
///
/// Created on: Mar 5, 2017
///     Author: alexen
///

#pragma once

#include <cstddef>
#include <functional>
#include <string_view>


namespace logger {
namespace tools {


using SliceHandler = std::function< void( std::string_view ) >;


/// Нарезает длинный текст кусками по @p chunkSize и передает в колбек @p cb
/// @param chunkSize размер порции в байтах, на которые нарезается длинный текст
/// @param data блок исходных данных
/// @param cb колбек, который вызывается для каждой порции текста
/// @throw кидает только те исключения, которые генерируются колбеком @p cb
void slice( const std::size_t chunkSize, std::string_view data, SliceHandler&& cb );


/// Перегрузка для записи результатов в std::ostream (вызывает первый вариант slice())
void slice( const std::size_t chunkSize, std::string_view data, std::ostream& os );


} // namespace tools
} // namespace logger
