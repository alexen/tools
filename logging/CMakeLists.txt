set(NAME logging)
set(HDRS
     syslog_ostreambuf.h
     syslogger.h
     tools.h
)
set(SRCS
     src/syslog_ostreambuf.cpp
     src/syslogger.cpp
     src/tools.cpp
)
add_library(${NAME} ${SRCS})
install(TARGETS ${NAME}
     ARCHIVE DESTINATION lib
     LIBRARY DESTINATION lib
)
install(FILES ${HDRS} DESTINATION include/tools/${NAME})