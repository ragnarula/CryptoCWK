cmake_minimum_required(VERSION 3.6)
project(CryptoCoursework)

set (CMAKE_CXX_STANDARD 11)
enable_testing()

add_executable(decrypt MainDecrypt.cpp Text.cpp Util.cpp Util.h MonoSolution.cpp MonoSolution.h VigenereSolution.cpp VigenereSolution.h LetterFrequency.cpp LetterFrequency.h)
add_executable(testapp MainTest.cpp Text.cpp TextTests.cpp Util.cpp Util.h UtilTests.cpp MonoSolution.cpp MonoSolution.h VigenereSolution.cpp VigenereSolution.h LetterFrequency.cpp LetterFrequency.h)
add_executable(shift Text.cpp MainShift.cpp Util.cpp MonoSolution.cpp MonoSolution.h VigenereSolution.cpp VigenereSolution.h LetterFrequency.cpp LetterFrequency.h)
add_executable(affine MainAffine.cpp Util.cpp Text.cpp MonoSolution.cpp MonoSolution.h VigenereSolution.cpp VigenereSolution.h LetterFrequency.cpp LetterFrequency.h)

add_test(CatchTests testapp)