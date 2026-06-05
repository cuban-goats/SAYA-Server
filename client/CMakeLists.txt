cmake_minimum_required(VERSION 3.16)
project(client CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(client
    src/main.cpp
    src/client/http.cpp
    src/client/Request.cpp
)

target_include_directories(client PRIVATE src)
