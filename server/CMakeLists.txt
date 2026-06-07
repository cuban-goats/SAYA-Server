cmake_minimum_required(VERSION 3.16)
project(server CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(server
    src/main.cpp
    src/http/http.cpp
    src/http/request/GetRq.cpp
    src/http/response/GetRes.cpp
)

target_include_directories(server PRIVATE include)
