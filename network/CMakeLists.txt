set(THIS network)
add_library(${THIS})
target_sources(
     ${THIS}
     PRIVATE
          src/error.cpp
          udp/src/utils.cpp
)

if(BUILD_TESTING)
     set(THIS_UTEST ${THIS}-test)
     add_executable(${THIS_UTEST}
          test/utils_test.cpp
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