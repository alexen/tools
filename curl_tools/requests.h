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

#include "types.h"


namespace curl_tools {
namespace requests {


long get(
     const types::CurlUptr& curl,
     const types::CurlHeadersListUptr& headers,
     const std::string& url,
     std::ostream& response,
     const boost::optional< boost::posix_time::time_duration >& connectionTimeout = boost::none,
     const boost::optional< boost::posix_time::time_duration >& requestTimeout = boost::none
     );


long get(
     const types::CurlUptr& curl,
     const std::string& url,
     std::ostream& response,
     const boost::optional< boost::posix_time::time_duration >& connectionTimeout = boost::none,
     const boost::optional< boost::posix_time::time_duration >& requestTimeout = boost::none
     );


long post(
     const types::CurlUptr& curl,
     const types::CurlHeadersListUptr& headers,
     const std::string& url,
     const char* const data,
     std::size_t size,
     std::ostream& response,
     const boost::optional< boost::posix_time::time_duration >& connectionTimeout = boost::none,
     const boost::optional< boost::posix_time::time_duration >& requestTimeout = boost::none
     );


long post(
     const types::CurlUptr& curl,
     const std::string& url,
     const char* const data,
     std::size_t size,
     std::ostream& response,
     const boost::optional< boost::posix_time::time_duration >& connectionTimeout = boost::none,
     const boost::optional< boost::posix_time::time_duration >& requestTimeout = boost::none
     );


} // namespace requests
} // namespace curl_tools
