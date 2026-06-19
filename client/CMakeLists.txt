cmake_minimum_required(VERSION 3.16)
project(client CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(client
    src/main.cpp
    src/client/http.cpp
    src/client/Request.cpp
)

target_include_directories(client PRIVATE src)
