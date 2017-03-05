///
/// tools.h
///
/// Created on: Mar 5, 2017
///     Author: alexen
///

#pragma once

#include <cstddef>
#include <functional>


namespace logger {
namespace tools {


/// Нарезает длинный текст кусками по @p chunkSize и передает в колбек @p cb
/// @param chunkSize размер порции в байтах, на которые нарезается длинный текст
/// @param text указатель на строку текста
/// @param size размер строки текста
/// @param cb колбек, который вызывается для каждой порции текста
/// @throw кидает только те исключения, которые генерируются колбеком @p cb
void slice( const std::size_t chunkSize, const char* text, const std::size_t size,
     std::function< void( const char*, std::size_t ) >&& cb );


/// Перегрузка для типа std::string (вызывает первый вариант slice())
void slice( const std::size_t chunkSize, const std::string& text,
     std::function< void( const char*, std::size_t ) >&& cb );


/// Перегрузка для записи результатов в std::ostream (вызывает первый вариант slice())
void slice( const std::size_t chunkSize, const char* text, const std::size_t size, std::ostream& os );


/// Перегрузка для типа std::string (вызывает первый вариант slice())
void slice( const std::size_t chunkSize, const std::string& text, std::ostream& os );


} // namespace tools
} // namespace logger
