///
/// funcs.h
///
/// Created on: Sep 28, 2017
///     Author: alexen
///

#pragma once

#include <cstddef>
#include <iosfwd>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <curlutil/base/errors.h>
#include <curlutil/base/types.h>


namespace tools {
namespace curl {
namespace base {
namespace utils {


/// Возвращает умный указатель на инициализированный объект CURL с проверкой ошибок
/// @throw errors::CurlError при возникновении ошибок инициализации
types::CurlUptr makeCurl();


/// Возвращает умный указатель на инициализированный объект curl_slist
///
/// Созданный указатель инициализирован значением nullptr, в дальнейшем
/// предполагается использование в функциях @p addSlistItem()
types::CurlSlistUptr makeSlist() noexcept;


/// Оборачивает указатель на динамическую строку, создаваемую CURLом в умный указатель
/// с автоочисткой с помощью функции @a curl_free()
types::CurlStringUptr makeString( char* s ) noexcept;


/// Конвертирует неразрешенные для URL символы из блока данных @a s размера @a len в их
/// шестнадцатеричые представления вида %NN
/// @return Указатель на c-style строку с нулевым терминатором
std::string urlEscape( const types::CurlUptr& curl, const char* s, const std::size_t len );


/// Перегрузка для работы с типом std::string
std::string urlEscape( const types::CurlUptr& curl, const std::string& data );


/// Перегрузка с выводом в выходной поток ввода-вывода
///
/// @note Так как URL (или произвольный блок данных) могут иметь значительную длину, целесообразнее
/// выводить результат в выходной поток ввода-вывода.
///
/// @throw CurlError в случае ошибки
void urlEscape( const types::CurlUptr& curl, const char* s, const std::size_t len, std::ostream& os );


/// Перегрузка для работы с типом std::string
void urlEscape( const types::CurlUptr& curl, const std::string& data, std::ostream& os );


/// Функция, обновляющая (расширяющая) список, на который указывает @p types::CurlSlistUptr
void addSlistItem( types::CurlSlistUptr& slist, const char* const item ) noexcept;


/// Перегрузка для типа const std::string&
/// @see void addSlistItem( types::CurlSlistUptr& slist, const char* const item );
void addSlistItem( types::CurlSlistUptr& slist, const std::string& item ) noexcept;


/// Перегрузка для семантики перемещения
/// @see void addSlistItem( types::CurlSlistUptr& slist, const char* const item );
void addSlistItem( types::CurlSlistUptr& slist, std::string&& item ) noexcept;


/// Устанавливает необходимые параметры для простой авторизации по логину/паролю
void setPlainAuth(
     const types::CurlUptr& curl,
     const std::string& login,
     const std::string& password
     ) noexcept;


/// Устанавливает таймаут для ожидания подключения к удаленному хосту
void setConnectionTimeout(
     const types::CurlUptr& curl,
     const boost::posix_time::time_duration& timeout
     ) noexcept;


/// Устанавливает таймаут для ожидания ответа на запрос от удаленного хоста
void setRequestTimeout(
     const types::CurlUptr& curl,
     const boost::posix_time::time_duration& timeout
     ) noexcept;


}}}}
