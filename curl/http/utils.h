///
/// funcs.h
///
/// Created on: Sep 28, 2017
///     Author: alexen
///

#pragma once

#include <iosfwd>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <tools/curl/base/types.h>
#include <tools/curl/http/types.h>


namespace tools {
namespace curl {
namespace http {
namespace utils {


base::types::CurlSlistUptr makeHttpHeaders( types::Headers&& headers );

void extendHttpHeaders(
     base::types::CurlSlistUptr& slist,
     types::Headers&& headers
     );

void extendHttpHeaders(
     base::types::CurlSlistUptr& slist,
     const std::string& key,
     const std::string& value
     );

void setBasicAuth(
     const base::types::CurlUptr& curl,
     const std::string& login,
     const std::string& password );

void setUserAgent( const base::types::CurlUptr& curl, const std::string& userAgent );

void setResponseHeadersOutput( const base::types::CurlUptr& curl, std::ostream& );


}}}}
