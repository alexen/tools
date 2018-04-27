set(NAME stopwatch)
set(HDRS stopwatch.h stopwatch_io.h)
set(SRCS src/stopwatch.cpp src/stopwatch_io.cpp)
add_library(${NAME} ${SRCS})
install(TARGETS ${NAME}
     ARCHIVE DESTINATION lib
     LIBRARY DESTINATION lib
)
install(FILES ${HDRS} DESTINATION include/tools/${NAME})