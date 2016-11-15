cmake_minimum_required(VERSION 3.6)
project(CryptoCoursework)

set (CMAKE_CXX_STANDARD 11)
enable_testing()

add_executable(decrypt MainDecrypt.cpp Text.cpp Helper.cpp Helper.h)
add_executable(testapp MainTest.cpp Text.cpp TextTests.cpp Helper.cpp Helper.h)
add_executable(shift Text.cpp MainShift.cpp Helper.cpp)
add_executable(affine MainAffine.cpp Helper.cpp Text.cpp)

add_test(CatchTests testapp)