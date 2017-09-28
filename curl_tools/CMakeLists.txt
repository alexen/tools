set(NAME curltools)
add_library(${NAME}
     utilities.cpp
     curl_raii.cpp
)
target_link_libraries(${NAME}
     ${CURL_LIBRARIES}
)