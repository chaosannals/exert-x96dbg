cmake_minimum_required(VERSION 3.20)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  message(STATUS "using ${CMAKE_CXX_COMPILER_ID}")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  message(STATUS "using ${CMAKE_CXX_COMPILER_ID}")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  message(STATUS "using ${CMAKE_CXX_COMPILER_ID}")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  message(STATUS "using ${CMAKE_CXX_COMPILER_ID}")
  # using Visual Studio C++
endif()

include(FetchContent)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(crackme)

add_subdirectory(crackcmd)
add_subdirectory(cracksdl2)
add_subdirectory(cracksehw)
add_subdirectory(crackwa)
