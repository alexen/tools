set(THIS stopwatch)
add_library(${THIS})
target_sources(
     ${THIS}
     PRIVATE
          src/stopwatch.cpp
          src/stopwatch_io.cpp
     PUBLIC
          stopwatch.h
          stopwatch_io.h
)
install(TARGETS ${THIS})

if(BUILD_TESTING)
     set(THIS_UTEST ${THIS}-test)
     add_executable(${THIS_UTEST}
          test/stopwatch_test.cpp
     )
     target_link_libraries(
          ${THIS_UTEST}
          PRIVATE
               ${THIS}
               gtest
               gtest_main
     )
     add_test(
          NAME ${THIS}
          COMMAND ${THIS_UTEST}
     )
endif()