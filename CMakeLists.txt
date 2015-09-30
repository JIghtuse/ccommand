project(ccommand)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wlogical-op -Werror")

add_definitions("-D_GNU_SOURCE")
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(ccommand SHARED
    include/ccommand.h
    src/ccommand.c)

add_subdirectory(tests)

add_executable(ping
    examples/ping.c)

target_link_libraries(ping ccommand)
