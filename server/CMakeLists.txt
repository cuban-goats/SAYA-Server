cmake_minimum_required(VERSION 3.16)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

if(APPLE AND NOT CMAKE_OSX_ARCHITECTURES)
  execute_process(COMMAND uname -m OUTPUT_VARIABLE HOST_ARCH OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_OSX_ARCHITECTURES "${HOST_ARCH}" CACHE STRING "")
endif()

project(server CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(server
    src/main.cpp
    src/http/http.cpp
    src/http/request/GetRq.cpp
    src/http/response/GetRes.cpp
    src/util/Util.cpp
    src/websocket/WebSocket.cpp
    src/crypt/Crypt.cpp
)

target_include_directories(server PRIVATE include)

if(APPLE)
  set(OPENSSL_ROOT_DIR "/opt/homebrew/opt/openssl" CACHE PATH "")
endif()
find_package(OpenSSL REQUIRED)
target_link_libraries(server PRIVATE OpenSSL::SSL OpenSSL::Crypto)
