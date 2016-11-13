cmake_minimum_required (VERSION 3.6)
project (crypt_breaker)

set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(PROJECT2_SRCS
        ${PROJECT_SOURCE_DIR}/Text.cpp
        ${PROJECT_SOURCE_DIR}/Main.cpp
        )

include_directories("${PROJECT_BINARY_DIR}")
add_executable(crypt_breaker ${PROJECT2_SRCS})
include_directories("${PROJECT_INCLUDE_DIR}")
