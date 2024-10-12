include(FetchContent)

FetchContent_Declare(
     curl
     URL       https://github.com/curl/curl/archive/refs/tags/curl-8_10_0.tar.gz
     URL_HASH  SHA256=eb4b60d49cb5427df14480b9ab369edbc897b7150230d2b0f38fdc7201e36dc4
     )

set(HTTP_ONLY            ON)
set(USE_LIBIDN2          OFF)
set(CURL_USE_LIBSSH2     OFF)
set(CURL_USE_LIBPSL      OFF)

FetchContent_MakeAvailable(curl)
