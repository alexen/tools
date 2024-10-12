///
/// funcs.h
///
/// Created on: Sep 28, 2017
///     Author: alexen
///

#pragma once

#include <iosfwd>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <curlutil/base/types.h>
#include <curlutil/http/types.h>


namespace tools {
namespace curl {
namespace http {
namespace utils {


/// Создает указатель на curl_slist в контексте HTTP-запросов и используется для создания HTTP-заголовков
/// @param headers HTTP-хедеры для инициализации
///
/// Пример использование с учетом стандарта C++11:
/// @code
/// const auto headers =
///      makeHttpHeaders({
///           { "Authorization",      "AUTHORIZATION_TYPE" },
///           { "X-Some-Spec-Header", "Some spec value" },
///           { "Expected",           "" } // Подавляем создание хедера "Expect: 100-continue"
///      });
///  @endcode
base::types::CurlSlistUptr makeHttpHeaders( types::Headers&& headers ) noexcept;


/// Обновлет (расширяет) текущий список HTTP-заголовков
///
/// @param slist существующий список HTTP-заголовков
/// @param headers дополнительные HTTP-заголовки
///
/// Пример использование с учетом стандарта c++11:
/// @code
/// auto headers =
///      makeHttpHeaders({
///           { "Authorization",      "AUTHORIZATION_TYPE" },
///           { "X-Some-Spec-Header", "Some spec value" },
///           { "Expected",           "" } // Подавляем создание хедера "Expect: 100-continue"
///      });
///
///  extendHttpHeaders( headers, {
///       { "X-Some-Another-Header", "Another header value" },
///       { "Content-Type",          "Specific-Content-Type" }
///  });
///
///  @endcode
void extendHttpHeaders(
     base::types::CurlSlistUptr& slist,
     types::Headers&& headers
     ) noexcept;


/// Перегрузка для более human-readable использования
///
/// Пример использование с учетом стандарта c++11:
/// @code
/// auto headers =
///      makeHttpHeaders({
///           { "Authorization",      "AUTHORIZATION_TYPE" },
///           { "X-Some-Spec-Header", "Some spec value" },
///           { "Expected",           "" } // Подавляем создание хедера "Expect: 100-continue"
///      });
///
///  extendHttpHeaders( headers, "X-Some-Another-Header", "Another header value" );
///  extendHttpHeaders( headers, "Expected", "" ); // Подавляем создание хедера "Expect: 100-continue"
///
///  @endcode
void extendHttpHeaders(
     base::types::CurlSlistUptr& slist,
     const std::string& key,
     const std::string& value
     ) noexcept;


/// Устанавливает параметры basic-авторизации для HTTP-протокола
void setBasicAuth(
     const base::types::CurlUptr& curl,
     const std::string& login,
     const std::string& password
     ) noexcept;


/// Устанавливает значение User-Agent для HTTP-протокола
void setUserAgent( const base::types::CurlUptr& curl, const std::string& userAgent ) noexcept;


/// Устанавливает выходной поток для записи HTTP-хедеров ответа удаленного сервера
void setResponseHeadersOutput( const base::types::CurlUptr& curl, std::ostream& ) noexcept;


}}}}
