///
/// types.h
///
/// Created on: Sep 28, 2017
///     Author: alexen
///

#pragma once

#include <map>


namespace tools {
namespace curl {
namespace http {
namespace types {


/// Предопределенный тип для HTTP-хедеров
using Headers = std::map< std::string, std::string >;


}}}}
