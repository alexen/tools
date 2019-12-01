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
/// - хранит сроковое значение префикса, который будет выводиться перед каждым сообщением;
/// - поддерживает простое отключение вывода некоторых сообщений;
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
/// // Также можно отключать некоторый (дебаговый, трассировочный) вывод внешним признаком
/// // который может задаваться извне, например, в конфиге программы или в качестве параметра
/// // командной строки
/// //
/// bool verboseLogging = getExternalParameter( "verbose" );
///
/// // Нижеследующая строка не будет ни сформирована, не выведена в лог, если verboseLogging == false
/// //
/// logger.debug( verboseLogging ) << "Some long debug text message";
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
          /// Выполняет установку внутренних переменных
          /// @param verbose признак подробного вывода (если false - сообшение не формируется и колбек не вызывается)
          /// @param os внешний буфер формирования строки сообщения
          /// @param flushMessageCb колбек, в который передается сформированное сообщение при разрушении объекта
          LogStream( bool verbose, std::ostringstream& os, std::function< void( std::string&& ) >&& flushMessageCb );

          /// Разрушает объект потока с записью сообщения в лог
          ///
          /// При разрушении объекта осуществляется передача сформированного сообщения в колбек
          /// после чего поток очищается
          /// @note Колбек вызывается только при установленном флаге verbose
          /// @attention Колбек не должен генерировать исключений!
          ~LogStream();

          /// Шаблонный оператор вывода в поток
          /// @note Формирование потока осуществляется только при установленном флаге @p verbose
          template< typename T >
          LogStream& operator<<( const T& t )
          {
               if( verbose_ )
               {
                    os_ << t;
               }
               return *this;
          }

     private:
          const bool verbose_ = true;
          std::ostringstream& os_;
          std::function< void( std::string&& ) > flushMessage_;
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
     /// @param verbose признак подробного вывода (отключает формирование сообщение и вывод его в лог)
     /// @return временный объект LogStream
     LogStream operator()( int severity, bool verbose = true );

     /// Аналог вызова operator() с параметром LOG_INFO
     LogStream info( bool verbose = true );

     /// Аналог вызова operator() с параметром LOG_DEBUG
     LogStream debug( bool verbose = true );

     /// Аналог вызова operator() с параметром LOG_WARNING
     LogStream warning( bool verbose = true );

     /// Аналог вызова operator() с параметром LOG_ERR
     LogStream error( bool verbose = true );

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
