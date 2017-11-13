set(NAME curltools)
add_library(${NAME}
     http/requests.cpp
     http/utils.cpp
     base/utils.cpp
     base/write_func.cpp
)
target_link_libraries(${NAME}
     ${CURL_LIBRARIES}
)
