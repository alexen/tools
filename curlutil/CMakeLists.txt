set(NAME curlutil)
set(HDRS
     base/errors.h
     base/types.h
     base/utils.h
     http/errors.h
     http/types.h
     http/utils.h
     http/requests.h
)
set(SRCS
     base/data_writer.cpp
     base/utils.cpp
     http/requests.cpp
     http/utils.cpp
)
add_library(${NAME} ${SRCS})
target_link_libraries(${NAME}
     ${CURL_LIBRARIES}
)
install(TARGETS ${NAME} LIBRARY DESTINATION lib)
install(FILES ${HDRS} DESTINATION include/tools/${NAME})