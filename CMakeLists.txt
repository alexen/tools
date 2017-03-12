cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++11)
add_definitions(-Wall -Werror -Wpedantic -Wextra)

include_directories(${CMAKE_SOURCE_DIR})

# Устанавливаем флаги для Debug-сборки
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -O0 -fno-inline")

add_subdirectory(stopwatch)
add_subdirectory(logger)
add_subdirectory(network)

set(NAME tools)
add_executable(${NAME} main.cpp)
target_link_libraries(${NAME} logger stopwatch network)