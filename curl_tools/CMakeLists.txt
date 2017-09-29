set(NAME curltools)
add_library(${NAME}
     utilities.cpp
)
target_link_libraries(${NAME}
     ${CURL_LIBRARIES}
)