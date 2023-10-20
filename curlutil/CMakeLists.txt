set(THIS curlutil)
add_library(${THIS})
target_sources(
     ${THIS}
     PRIVATE
          base/data_writer.cpp
          base/utils.cpp
          http/requests.cpp
          http/utils.cpp
     PUBLIC
          base/errors.h
          base/types.h
          base/utils.h
          http/errors.h
          http/types.h
          http/utils.h
          http/requests.h
)
target_link_libraries(
     ${THIS}
     PRIVATE
          ${CURL_LIBRARIES}
)
install(TARGETS ${THIS})
# @todo Installation for headers