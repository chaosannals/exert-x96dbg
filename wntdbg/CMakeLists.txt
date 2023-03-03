cmake_minimum_required(VERSION 3.24)

if (NOT WIN32)
	message(FATAL_ERROR "mast Windows.")
endif()

add_subdirectory(buger)
add_subdirectory(bugerw)
add_subdirectory(debuger)
