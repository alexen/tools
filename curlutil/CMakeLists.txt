set(NAME curlutil)
add_library(${NAME}
     http/requests.cpp
     http/utils.cpp
     base/utils.cpp
     base/data_writer.cpp
)
target_link_libraries(${NAME}
     ${CURL_LIBRARIES}
)
