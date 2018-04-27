set(NAME logger)
set(HDRS syslogger.h tools.h)
set(SRCS src/syslogger.cpp src/tools.cpp)
add_library(${NAME} ${SRCS})
install(TARGETS ${NAME}
     ARCHIVE DESTINATION lib
     LIBRARY DESTINATION lib
)
install(FILES ${HDRS} DESTINATION include/tools/${NAME})