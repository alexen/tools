set(THIS logging)
add_library(${THIS})
target_sources(
     ${THIS}
     PRIVATE
          src/syslog_ostreambuf.cpp
          src/syslogger.cpp
          src/tools.cpp
     PUBLIC
          syslog_ostreambuf.h
          syslogger.h
          tools.h
)
install(TARGETS ${THIS})
# @todo Installation for headers