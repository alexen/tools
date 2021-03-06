cmake_minimum_required(VERSION 3.5)

project(tools)

add_definitions(-std=c++17)
add_definitions(-Wall -Werror -Wextra -pedantic)

set(LOCAL_ROOT $ENV{HOME}/.local)
set(LOCAL_INCLUDE_DIR ${LOCAL_ROOT}/include)

include_directories(${CMAKE_SOURCE_DIR})

# Устанавливаем флаги для Debug-сборки
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -O0 -fno-inline")

# Настройки сборки проекта
set(BUILD_SHARED_LIBS ON CACHE BOOLEAN "")
set(TEST_ENABLED ON CACHE BOOLEAN "")
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "")

message(STATUS "Build shared libs: ${BUILD_SHARED_LIBS}")
message(STATUS "Tests enabled: ${TEST_ENABLED}")

set(BOOST_ROOT ${LOCAL_ROOT})
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_definitions(-DBOOST_ALLOW_DEPRECATED_HEADERS)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

if(TEST_ENABLED)
     include(CTest)
     add_subdirectory(googletest)
     include_directories(googletest/googletest/include)
     enable_testing()
endif()

add_subdirectory(stopwatch)
add_subdirectory(logging)
add_subdirectory(network)
add_subdirectory(curlutil)

set(NAME tools)
add_executable(${NAME} main.cpp)
target_link_libraries(${NAME}
     logging
     stopwatch
     network
     curlutil
)
