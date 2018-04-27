cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++17)
add_definitions(-Wall -Werror -Wextra -pedantic)

include_directories(${CMAKE_SOURCE_DIR})

# Устанавливаем флаги для Debug-сборки
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -O0 -fno-inline")

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

add_subdirectory(stopwatch)
add_subdirectory(logger)
add_subdirectory(network)
add_subdirectory(curlutil)

set(NAME tools)
add_executable(${NAME} main.cpp)
target_link_libraries(${NAME} logger stopwatch network curlutil)
