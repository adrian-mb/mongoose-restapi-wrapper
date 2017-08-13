cmake_minimum_required(VERSION 3.1)

project(webserver CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")

add_library(webserver STATIC
    Dispatcher.cpp
    HttpMethod.cpp
    HttpRequest.cpp
    HttpResponse.cpp
    TokenTree.cpp
    Server.cpp)
