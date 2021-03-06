project(ccommand)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wlogical-op -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wlogical-op -Werror -Weffc++")

add_definitions("-D_GNU_SOURCE")
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(ccommand SHARED
    include/ccommand.h
    src/ccommand.c)

add_executable(ping
    examples/ping.c)

target_link_libraries(ping ccommand)

add_executable(sh
    examples/sh.cxx)

target_link_libraries(sh ccommand)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

install(TARGETS ccommand
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
