///
/// requests.h
///
/// Created on: Oct 24, 2017
///     Author: alexen
///

#pragma once

#include <cstddef>
#include <iosfwd>

#include <boost/optional/optional.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>

#include <curlutil/base/types.h>


namespace tools {
namespace curl {
namespace http {
namespace requests {


/// Реализует HTTP-запрос GET
///
/// Использует внутренние функции-посредники @p request() и функцию @p getHttpStatus()
///
/// @param curl указатель CurlUptr, инициализированный с помощью функции @see base::utils::makeCurl()
/// @param headers HTTP-хедеры - указатель на CurlSlistUptr, инициализированный с помощью функции @see base::utils::makeSlist()
/// @param url URL или IP-адрес удаленного хоста
/// @param response ссылка на выходной поток для сохранения ответа удаленного сервера
/// @param connectionTimeout таймаут для ожидания подключения к удаленному хосту
/// @param requestTimeout таймаут для ожидания ответа на запрос от удаленного хоста
/// @throw errors::HttpRequestError при любых ошибках, в том числе при возврате ответа HTTP отличного от 200
long get(
     const base::types::CurlUptr& curl,
     const base::types::CurlSlistUptr& headers,
     const std::string& url,
     std::ostream& response,
     const boost::optional< boost::posix_time::time_duration >& connectionTimeout = boost::none,
     const boost::optional< boost::posix_time::time_duration >& requestTimeout = boost::none
     );


/// Перегрузка для использования запроса без HTTP-хедеров
long get(
     const base::types::CurlUptr& curl,
     const std::string& url,
     std::ostream& response,
     const boost::optional< boost::posix_time::time_duration >& connectionTimeout = boost::none,
     const boost::optional< boost::posix_time::time_duration >& requestTimeout = boost::none
     );


/// Реализует HTTP-запрос POST
///
/// Использует внутренние функции-посредники @p request() и функцию @p getHttpStatus()
///
/// @param curl указатель CurlUptr, инициализированный с помощью функции @see base::utils::makeCurl()
/// @param headers HTTP-хедеры - указатель на CurlSlistUptr, инициализированный с помощью функции @see base::utils::makeSlist()
/// @param url URL или IP-адрес удаленного хоста
/// @param data указатель на передаваемые на удаленный сервер данные
/// @param size размер данных, отправляемых на удаленный сервер
/// @param response ссылка на выходной поток для сохранения ответа удаленного сервера
/// @param connectionTimeout таймаут для ожидания подключения к удаленному хосту
/// @param requestTimeout таймаут для ожидания ответа на запрос от удаленного хоста
/// @throw errors::HttpRequestError при любых ошибках, в том числе при возврате ответа HTTP отличного от 200
long post(
     const base::types::CurlUptr& curl,
     const base::types::CurlSlistUptr& headers,
     const std::string& url,
     const char* const data,
     std::size_t size,
     std::ostream& response,
     const boost::optional< boost::posix_time::time_duration >& connectionTimeout = boost::none,
     const boost::optional< boost::posix_time::time_duration >& requestTimeout = boost::none
     );


/// Перегрузка для использования запроса без HTTP-хедеров
long post(
     const base::types::CurlUptr& curl,
     const std::string& url,
     const char* const data,
     std::size_t size,
     std::ostream& response,
     const boost::optional< boost::posix_time::time_duration >& connectionTimeout = boost::none,
     const boost::optional< boost::posix_time::time_duration >& requestTimeout = boost::none
     );


}}}}
