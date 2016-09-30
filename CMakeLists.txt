cmake_minimum_required(VERSION 3.6)
project(client_server_file)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package (Threads)
set(SOURCE_FILES main.c)
add_executable(client_server_file ${SOURCE_FILES})
target_link_libraries (client_server_file ${CMAKE_THREAD_LIBS_INIT})