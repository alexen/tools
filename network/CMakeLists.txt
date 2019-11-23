set(EXECNAME network)
add_library(${EXECNAME}
    udp/src/utils.cpp
)

if(BUILD_TESTING)
     set(TESTNAME ${EXECNAME}-test)
     add_executable(${TESTNAME} test/utils_test.cpp)
     target_link_libraries(${TESTNAME} gtest gtest_main)
     add_test(${EXECNAME} ${TESTNAME})
endif()