///
/// logger.cpp
///
/// Created on: Mar 4, 2017
///     Author: alexen
///

#include <logger/syslogger.h>
#include <logger/tools.h>
#include <syslog.h>

namespace logger {


SysLogger::LogStream::LogStream( std::ostringstream& os, const std::function< void( std::string&& ) >& flushMessageCb )
     : os_( os ), flushMessage_( flushMessageCb )
{}


SysLogger::LogStream::~LogStream()
{
     /// Функция не должна кидать исключениЙ
     flushMessage_( os_.str() );
     os_.str( "" );
}


void SysLogger::flush( int severity, const std::string& prefix, std::string&& message )
{
     tools::slice( 4096, message,
          [ severity, &prefix ]( const char* ptr, std::size_t size )
          {
               /// static_cast подавляет предупреждение компилятора
               /// "warning: field precision specifier ‘.*’ expects argument of type ‘int’..."
               syslog( severity, "%s: %.*s", prefix.c_str(), static_cast< int >( size ), ptr );
          }
     );
}


SysLogger::SysLogger( const std::string& prefix )
     : prefix_( prefix )
{}


SysLogger::SysLogger( std::string&& prefix )
     : prefix_( std::move( prefix ) )
{}


SysLogger::LogStream SysLogger::operator()( int severity )
{
     return LogStream( ostr_, std::bind( flush, severity, std::cref( prefix_ ), std::placeholders::_1 ) );
}


SysLogger::LogStream SysLogger::info()
{
     return (*this)( LOG_INFO );
}


SysLogger::LogStream SysLogger::debug()
{
     return (*this)( LOG_DEBUG );
}


SysLogger::LogStream SysLogger::warning()
{
     return (*this)( LOG_WARNING );
}


SysLogger::LogStream SysLogger::error()
{
     return (*this)( LOG_ERR );
}


} // namespace logger
