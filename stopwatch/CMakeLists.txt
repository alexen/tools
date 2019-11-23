set(NAME stopwatch)
set(HDRS stopwatch.h stopwatch_io.h)
set(SRCS src/stopwatch.cpp src/stopwatch_io.cpp)
add_library(${NAME} ${SRCS})
install(TARGETS ${NAME}
     ARCHIVE DESTINATION lib
     LIBRARY DESTINATION lib
)
install(FILES ${HDRS} DESTINATION include/tools/${NAME})

if(BUILD_TESTING)
     set(TESTNAME ${NAME}-test)
     add_executable(${TESTNAME} test/stopwatch_test.cpp)
     target_link_libraries(${TESTNAME} ${NAME} gtest gtest_main)
     add_test(${NAME} ${TESTNAME})
endif()