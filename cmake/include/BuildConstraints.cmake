if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_BUILD_DIR)
     message(FATAL_ERROR "In-source build is prohibited")
endif()

if(NOT CMAKE_BUILD_TYPE)
     set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
     message(STATUS "Use default build type: ${CMAKE_BUILD_TYPE}")
endif()
