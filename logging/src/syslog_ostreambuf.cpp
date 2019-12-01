/// @file
/// @brief
/// @copyright Copyright (c) InfoTeCS. All Rights Reserved.

#include <logging/syslog_ostreambuf.h>
#include <syslog.h>


namespace tools {
namespace logging {


namespace {
namespace aux {


void syslogReport( const std::string& prefix, int severity, const char* s, int len )
{
     syslog( severity, "%.*s: %.*s", static_cast< int >( prefix.size() ), prefix.data(), len, s );
}


void syslogReport( int severity, const char* s, int len )
{
     syslog( severity, "%.*s", len, s );
}


} // namespace aux
} // namespace {unnamed}



Ostreambuf::~Ostreambuf()
{
     sync();
}


Ostreambuf::Ostreambuf( std::string&& prefix )
     : Ostreambuf::Base{}
     , prefix_{ std::move( prefix ) }
{
     resetBuffer();
}


Ostreambuf::Ostreambuf()
     : Ostreambuf{ "" }
{}


void Ostreambuf::resetBuffer()
{
     Base::setp( &buffer_[ 0 ], &buffer_[ 0 ] + buffer_.size() );
}


bool Ostreambuf::isBufferEmpty() const
{
     return Base::pbase() == Base::pptr();
}


Ostreambuf::int_type Ostreambuf::overflow( int_type c )
{
     sync();
     return Base::sputc( c );
}

std::streamsize Ostreambuf::xsputn( const char* s, std::streamsize size )
{
     static constexpr auto LF = '\n';
     if( size > 0 )
     {
          auto start = s;
          const auto end = s + size;
          bool lf = false;
          for( auto curr = start; curr != end; ++curr )
          {
               if( *curr == LF )
               {
                    if( !lf )
                    {
                         Base::xsputn( start, curr - start );
                         sync();
                         lf = true;
                    }
               }
               else
               {
                    if( lf )
                    {
                         start = curr;
                         lf = false;
                    }
               }
          }
          Base::xsputn( start, end - start );
     }
     return size;
}

Ostreambuf::int_type Ostreambuf::sync()
{
     if( !isBufferEmpty() )
     {
          if( !prefix_.empty() )
          {
               aux::syslogReport( prefix_, LOG_INFO, Base::pbase(), Base::pptr() - Base::pbase() );
          }
          else
          {
               aux::syslogReport( LOG_INFO, Base::pbase(), Base::pptr() - Base::pbase() );
          }
          resetBuffer();
     }
     return 0;
}


} // namespace logging
} // namespace tools
