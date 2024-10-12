add_library(
     curlutil
          base/data_writer.cpp
          base/utils.cpp
          http/requests.cpp
          http/utils.cpp
)
target_link_libraries(
     curlutil
     PRIVATE
          CURL::libcurl
)
target_include_directories(
     curlutil
     PUBLIC
          ${CMAKE_CURRENT_LIST_DIR}/include
     )
add_library(${PROJECT_NAME}::curlutil ALIAS curlutil)
install(TARGETS curlutil)
