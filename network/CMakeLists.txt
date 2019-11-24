set(LIBNAME network)
add_library(${LIBNAME}
     src/error.cpp
     udp/src/utils.cpp
)

if(BUILD_TESTING)
     set(TESTNAME ${LIBNAME}-test)
     add_executable(${TESTNAME} test/utils_test.cpp)
     target_link_libraries(${TESTNAME} ${LIBNAME} gtest gtest_main)
     add_test(${LIBNAME} ${TESTNAME})
endif()