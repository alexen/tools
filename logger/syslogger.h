///
/// logger.h
///
/// Created on: Mar 4, 2017
///     Author: alexen
///

#pragma once

#include <iosfwd>
#include <sstream>
#include <functional>


namespace logger {


/// Класс для вывода сообщений в syslog:
/// - поддерживающий формирование сообщений с помощью потокового вывода;
/// - обеспечивает нарезку длинных сообщений на порции перед выводом в syslog;
/// - хранит сроковое значение префикса, который будет выводиться перед каждым сообщением.
///
/// Для формирования сообщений используется потоковый объект std::ostringstream, который
/// создается только один раз при создании объекта SysLogger.
///
/// Пример использования:
/// @code
/// // Создаем какой-то интересный нам префикс
/// //
/// std::string prefix = "{" + boost::uuids::to_string( authPersonId ) + "}";
///
/// // Создаем объект логгера
/// //
/// logger::SysLogger logger( std::move( prefix ) );
///
/// // Пишем сообщение в лог (поддерживается вывод любых объектов, для которых существует operator<<())
/// //
/// logger( LOG_INFO ) << "Some text info, int " << 101 << ", time: " << boost::posix_time::second_clock::now();
///
/// // Или более удобная форма
/// //
/// logger.info() << "Text, " << boost::posix_time::second_clock::now() << ", pi: " << 3.1416;
///
/// @endcode
class SysLogger
{
     /// Внутренний тип, обеспечивающий формирование сообщения с помощью операторов потокового вывода.
     class LogStream
     {
     public:
          /// Создает объект потока
          ///
          /// Выполняет установку внутренних переменных (все переменные - лишь ссылки на объекты)
          LogStream( std::ostringstream& os, const std::function< void( std::string&& ) >& flushMessageCb );

          /// Разрушает объект потока с записью сообщения в лог
          ///
          /// При разрушении объекта осуществляется передача сформированного сообщения в колбек
          /// после чего поток очищается
          /// @attention Колбек не должен генерировать исключений!
          ~LogStream();

          /// Шаблонный оператор вывода в поток
          template< typename T >
          LogStream& operator<<( const T& t )
          {
               os_ << t;
               return *this;
          }

     private:
          std::ostringstream& os_;
          const std::function< void( std::string&& ) >& flushMessage_;
     };

public:
     /// Создает объект логгера
     ///
     /// Сохраняет созданный пользователем префикс во внутренней переменной и создает поток вывода
     explicit SysLogger( const std::string& prefix );

     /// Перегрузка для move-семантики
     explicit SysLogger( std::string&& prefix );

     /// Переопределенный оператор вызова для вывода сообщения в лог
     ///
     /// Возвращает временный объект @p LogStream, который в свою очередь поддерживает
     /// формирование сообщения с помощью операторов вывода в поток. В конструктор временного
     /// объекта @p LogStream в качестве колбека передается функция flush(), связанная с предустановленными
     /// параметрами с помощью std::bind().
     /// @param severity уровень сообщения (макросы LOG_* из файла syslog.h)
     /// @return временный объект LogStream
     LogStream operator()( int severity );

     /// Аналог вызова operator() с параметром LOG_INFO
     LogStream info();

     /// Аналог вызова operator() с параметром LOG_DEBUG
     LogStream debug();

     /// Аналог вызова operator() с параметром LOG_WARNING
     LogStream warning();

     /// Аналог вызова operator() с параметром LOG_ERR
     LogStream error();

private:
     /// Обеспечивает запись сообщения непосредственно в лог с помощью вызова функции syslog()
     ///
     /// Вывод подготовленного сообщения в лог осуществляется не напрямую, а посредством функции
     /// logger::tools::slice(), которая разбивает длинное сообщение на куски меньшего размера для
     /// того, чтобы большие объемы информации не терялись, а попадали в лог.
     /// Перед каждым куском текста выводится установленный пользователем @p prefix
     static void flush( int severity, const std::string& prefix, std::string&& message );

     std::ostringstream ostr_;
     std::string prefix_;
};


} // namespace logger
