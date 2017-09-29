cmake_minimum_required(VERSION 3.5)
add_definitions(-std=c++11)
add_definitions(-Wall -Werror -Wextra -pedantic)
include_directories(${CMAKE_SOURCE_DIR})
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
set(NAME using_curl)
add_subdirectory(curl_tools)
add_executable(${NAME}
     main.cpp
)
target_link_libraries(${NAME}
     curltools
)