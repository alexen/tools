///
/// funcs.h
///
/// Created on: Sep 28, 2017
///     Author: alexen
///

#pragma once

#include <iosfwd>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include "types.h"


namespace curl_tools {
namespace utilities {


types::CurlUptr makeCurl();


types::CurlHeadersListUptr makeHeadersList( types::Headers&& headers );


void updateHeadersList( types::CurlHeadersListUptr& existing, types::Headers&& headers );


void setBasicAuth(
     const types::CurlUptr& curl,
     const std::string& login,
     const std::string& password );


void setUserAgent( const types::CurlUptr& curl, const std::string& userAgent );


void setResponseHeadersOutput( const types::CurlUptr& curl, std::ostream& );


void setConnectionTimeout(
     const types::CurlUptr& curl,
     const boost::posix_time::time_duration& timeout
     );


void setRequestTimeout(
     const types::CurlUptr& curl,
     const boost::posix_time::time_duration& timeout
     );


} // namespace utilities
} // namespace curl_tools
