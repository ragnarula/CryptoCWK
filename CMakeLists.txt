cmake_minimum_required(VERSION 3.6)
project(CryptoCoursework)

set (CMAKE_CXX_STANDARD 11)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${dir}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${dir}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")
enable_testing()

add_executable(decrypt MainDecrypt.cpp Text.cpp Util.cpp Util.h AffineSolution.cpp AffineSolution.h VigenereSolution.cpp VigenereSolution.h LetterCount.cpp LetterCount.h MonoSubstitutionSolver.cpp MonoSubstitutionSolver.h stats.h)
add_executable(testapp MainTest.cpp Text.cpp TextTests.cpp Util.cpp Util.h UtilTests.cpp AffineSolution.cpp AffineSolution.h VigenereSolution.cpp VigenereSolution.h LetterCount.cpp LetterCount.h MonoSubstitutionSolver.cpp MonoSubstitutionSolver.h MonoSubstitutionSolverTests.cpp stats.h)
add_executable(shift Text.cpp MainShift.cpp Util.cpp AffineSolution.cpp AffineSolution.h VigenereSolution.cpp VigenereSolution.h LetterCount.cpp LetterCount.h)
add_executable(affine MainAffine.cpp Util.cpp Text.cpp AffineSolution.cpp AffineSolution.h VigenereSolution.cpp VigenereSolution.h LetterCount.cpp LetterCount.h)
add_executable(vigenere MainVigenere.cpp Util.cpp Text.cpp AffineSolution.cpp AffineSolution.h VigenereSolution.cpp VigenereSolution.h LetterCount.cpp LetterCount.h)

add_test(CatchTests testapp)