cmake_minimum_required(VERSION 3.6)
project(CryptoCoursework)

set (CMAKE_CXX_STANDARD 11)
enable_testing()

add_executable(decrypt MainDecrypt.cpp Text.cpp Util.cpp Util.h)
add_executable(testapp MainTest.cpp Text.cpp TextTests.cpp Util.cpp Util.h UtilTests.cpp)
add_executable(shift Text.cpp MainShift.cpp Util.cpp)
add_executable(affine MainAffine.cpp Util.cpp Text.cpp)

add_test(CatchTests testapp)