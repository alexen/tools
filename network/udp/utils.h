///
/// func.h
///
/// Created on: Mar 12, 2017
///     Author: alexen
///

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <system_error>


namespace tools {
namespace network {
namespace udp {


/// Класс для хранения данных UDP-соединения
class Connection
{
private:
     /// Внутренний класс для хранения универсального адреса (IPv4 или IPv6)
     struct UniversalSockaddr
     {
          UniversalSockaddr() noexcept;
          UniversalSockaddr( const sockaddr* sa, socklen_t salen ) noexcept;

          const socklen_t addrlen = 0;
          union {
               sockaddr_in sa;
               sockaddr_in6 sa6;
          }
          addr;
     };

public:
     /// Конструктор по-умолчанию
     ///
     /// Используется только для случаев ошибочных ситуаций, все поля структуры заполнены нулями
     Connection() noexcept {}

     /// Основной конструктор
     ///
     /// Конструктор просто заполняет внутренние переменные, никаких дополнительных вызовов не производится
     /// @param sfd файловый дескриптор открытого сокета UDP
     /// @param fam семейство протоколов (AF_INET или AF_INET6)
     /// @param sa указатель на структуру sockaddr, содержащую данные об IP-адресе (IPv4 или IPv6)
     /// @param salen длина структуры sockaddr (зависит от версии протокола IP)
     Connection( int sfd, int fam, const sockaddr* sa, socklen_t salen ) noexcept;

     /// Осуществляет закрытие сокета
     ///
     /// @attention
     /// Необходимо следить за тем, чтобы не было лишних вызовов деструктора, например, при создании временных переменных
     /// По этой причине необходимо избегать следующих конструкций:
     /// @code
     /// Connection someFunctionDoingConnection( ... )
     /// {
     ///      // Объявляем переменную как константную ссылку на временный объект (именно в этом кроется ошибка!)
     ///      const auto& c = connect( ... );
     ///
     ///      // ...
     ///      // осуществляем различные действия и проверки
     ///      // ...
     ///
     ///      // Возвращаем объект наружу
     ///      return c;
     /// }
     /// @endcode
     /// В этом случае будет вызван конструктор копирования (совершенно лишний!), а зетем деструктор, в котором
     /// сокет будет закрыт
     ~Connection() noexcept;

     const int sockfd = 0;
     const int family = 0;
     const UniversalSockaddr addr;
};


/// Возвращает структуру с данными открытого UDP-соединения, в случае ошибок заполняет переменную @p ec
/// @param hostname имя удаленного хоста или IP адрес (поддерживаются обе версии протокола IP)
/// @param port удаленный порт подключения
/// @param[out] ec ссылка на объект @p std::error_code, в которую будет помещена информация об ошибке при ее возникновении
/// @return структура с информацией о подключении UDP
Connection connect( const char* const hostname, int port, std::error_code& ec ) noexcept;


/// Возвращает структуру с данными открытого UDP-соединения, но в случае ошибки выбрасывается исключение
/// @throw std::system_error в случае ошибок подключения
Connection connect( const char* const hostname, int port );


/// Отправляет данные в предварительно созданное соединение @p Connection
/// @param c Созданное соединение UDP
/// @param data Указатель на начало пересылаемых данных
/// @param datalen Длина передаваемых данных
/// @return количество отправленных данных в байтах, в случае ошибки возвращается -1 и устанавливается errno
int send( const Connection& c, const char* data, std::size_t datalen ) noexcept;


/// Перегрузка для типа @p std::string
int send( const Connection& c, const std::string& message ) noexcept;


/// Отправляет данные по UDP-протоколу в @p hostname и @p port,
/// соединение открывается и закрывается автоматически при каждой отправке
///
/// @note Осуществляется неявняй вызов функций connect()
/// @param hostname имя удаленного хоста или IP адрес (поддерживаются обе версии протокола IP)
/// @param port удаленный порт подключения
/// @param data Указатель на начало пересылаемых данных
/// @param datalen Длина передаваемых данных
/// @param[out] ec ссылка на объект @p std::error_code, в которую будет помещена информация об ошибке при ее возникновении
/// @return количество отправленных данных в байтах, в случае ошибки возвращается -1 и устанавливается errno
/// @note Формирование переменной @p ec происходит только при внутреннем вызове функции connect()
int send( const char* const hostname, int port, const char* data, std::size_t datalen, std::error_code& ec ) noexcept;


/// Перегрузка для типа @p std::string
int send( const char* const hostname, int port, const std::string& message, std::error_code& ec ) noexcept;


/// Аналогичные функции отправки данных по UDP-протоколу, но генерирующие исключения в случае возникновения ошибок
/// @throw std::system_error при ошибках соединения
int send( const char* const hostname, int port, const char* data, std::size_t datalen );


/// Перегрузка для типа @p std::string, генерирующая исключение в случае возникновения ошибок
/// @throw std::system_error при ошибках соединения
int send( const char* const hostname, int port, const std::string& message );


} // namespace udp
} // namespace network
} // namespace tools
