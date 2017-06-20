cmake_minimum_required(VERSION 3.5)
add_definitions(-std=c++11)
include_directories(${CMAKE_SOURCE_DIR})
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
set(NAME using_curl)
add_executable(${NAME}
     main.cpp
)
target_link_libraries(${NAME}
     ${CURL_LIBRARIES}
)