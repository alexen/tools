set(NAME logger)
add_library(${NAME} src/syslogger.cpp src/tools.cpp)
install(TARGETS ${NAME} LIBRARY DESTINATION lib)
install(FILES syslogger.h DESTINATION include/logger)