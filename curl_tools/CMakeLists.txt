set(NAME curltools)
add_library(${NAME}
     inner.cpp
     requests.cpp
     utilities.cpp
)
target_link_libraries(${NAME}
     ${CURL_LIBRARIES}
)