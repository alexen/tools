cmake_minimum_required(VERSION 3.22)

project(tools)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

add_definitions(-Wall -Werror -Wextra -Wpedantic)

set(LOCAL_ROOT $ENV{HOME}/.local)
set(LOCAL_INCLUDE_DIR ${LOCAL_ROOT}/include)

include_directories(${CMAKE_SOURCE_DIR})

# Устанавливаем флаги для Debug-сборки
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -O0 -fno-inline")

# Настройки сборки проекта
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libs by default")
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build Debug configuration by default")

message(STATUS "Build shared libs: ${BUILD_SHARED_LIBS}")
message(STATUS "Tests enabled: ${TEST_ENABLED}")

find_package(Boost REQUIRED COMPONENTS)

add_definitions(-DBOOST_ALLOW_DEPRECATED_HEADERS)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

include(CTest)

if(BUILD_TESTING)
     add_subdirectory(googletest)
     include_directories(googletest/googletest/include)
endif()

add_subdirectory(stopwatch)
add_subdirectory(logging)
add_subdirectory(network)
add_subdirectory(curlutil)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(
     ${PROJECT_NAME}
     PRIVATE
          logging
          stopwatch
          network
          curlutil
)
