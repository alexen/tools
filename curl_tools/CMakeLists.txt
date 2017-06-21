set(NAME curltools)
add_library(${NAME}
     curl_raii.cpp
)
target_link_libraries(${NAME}
     ${CURL_LIBRARIES}
)