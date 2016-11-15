cmake_minimum_required(VERSION 3.6)
project(CryptoCoursework)

set (CMAKE_CXX_STANDARD 11)
enable_testing()

add_executable(app Main.cpp Text.cpp)
add_executable(testapp MainTest.cpp Text.cpp TextTests.cpp)
add_executable(shift Text.cpp MainShift.cpp)

add_test(CatchTests testapp)