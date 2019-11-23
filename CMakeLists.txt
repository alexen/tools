cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++17)
add_definitions(-Wall -Werror -Wextra -pedantic)

set(LOCAL_ROOT $ENV{HOME}/.local)
set(LOCAL_INCLUDE_DIR ${LOCAL_ROOT}/include)

include_directories(${CMAKE_SOURCE_DIR})

# Устанавливаем флаги для Debug-сборки
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -O0 -fno-inline")

set(BOOST_ROOT ${LOCAL_ROOT})
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_definitions(-DBOOST_ALLOW_DEPRECATED_HEADERS)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

add_subdirectory(stopwatch)
add_subdirectory(logger)
add_subdirectory(network)
add_subdirectory(curlutil)

set(NAME tools)
add_executable(${NAME} main.cpp)
target_link_libraries(${NAME} logger stopwatch network curlutil)
