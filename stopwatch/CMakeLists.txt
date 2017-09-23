set(NAME stopwatch)
add_library(${NAME} src/stopwatch.cpp src/stopwatch_io.cpp)
install(TARGETS ${NAME} LIBRARY DESTINATION lib)
install(FILES stopwatch.h stopwatch_io.h DESTINATION include/stopwatch)