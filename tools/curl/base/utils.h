///
/// funcs.h
///
/// Created on: Sep 28, 2017
///     Author: alexen
///

#pragma once

#include <cstddef>
#include <iosfwd>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <tools/curl/base/types.h>


namespace tools {
namespace curl {
namespace base {
namespace utils {


types::CurlUptr makeCurl();

types::CurlSlistUptr makeSlist();

void addSlistItem( types::CurlSlistUptr& slist, const char* const item );
void addSlistItem( types::CurlSlistUptr& slist, const std::string& item );
void addSlistItem( types::CurlSlistUptr& slist, std::string&& item );

void setPlainAuth(
     const types::CurlUptr& curl,
     const std::string& login,
     const std::string& password
     );

void setConnectionTimeout(
     const types::CurlUptr& curl,
     const boost::posix_time::time_duration& timeout
     );

void setRequestTimeout(
     const types::CurlUptr& curl,
     const boost::posix_time::time_duration& timeout
     );


}}}}
