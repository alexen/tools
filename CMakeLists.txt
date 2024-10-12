cmake_minimum_required(VERSION 3.15)

project(tools)

# Modern CMake:
# - use different directories for include files and modules
# - use CMAKE_CURRENT_LIST_DIR instead of CMAKE_CURRENT_SOURCE_DIR
#
list(APPEND CMAKE_MODULE_PATH
     ${CMAKE_CURRENT_LIST_DIR}/cmake/include
     ${CMAKE_CURRENT_LIST_DIR}/cmake/modules
     )

include(BuildConstraints)

# Modern CMake: search GTest, if not found - build it
find_package(GTest QUIET)
if(NOT GTest_FOUND)
     include(GTest)
endif()

# Modern CMake: use main project target to accumulate
# and propagate global project properties and parameters
add_library(${PROJECT_NAME} INTERFACE)
set_target_properties(
     ${PROJECT_NAME}
     PROPERTIES
          CXX_STANDARD 17
          CXX_STANDARD_REQUIRED ON
          CXX_EXTENSIONS OFF
     )

target_compile_options(
     ${PROJECT_NAME}
     INTERFACE
          -Wall
          -Werror
          -Wextra
          -pedantic
          -pedantic-error
          $<$<CONFIG:Debug>:-ggdb3 -O0 -fno-inline>
     )

target_include_directories(
     ${PROJECT_NAME}
     INTERFACE
          ${CMAKE_CURRENT_LIST_DIR}
     )

return()

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
