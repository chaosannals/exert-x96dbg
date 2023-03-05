cmake_minimum_required(VERSION 3.24)

include(FetchContent)

set(ALL_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/all")

if (NOT WIN32)
	message(FATAL_ERROR "mast Windows.")
endif()

# elements 库引入
FetchContent_Declare(
    elements
    GIT_REPOSITORY git@github.com:cycfi/elements.git
    # GIT_TAG 这库作者不打标签- -
)
FetchContent_Populate(elements)
set(ELEMENTS_ROOT ${elements_SOURCE_DIR})
get_filename_component(ELEMENTS_ROOT "${ELEMENTS_ROOT}" ABSOLUTE)
set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${ELEMENTS_ROOT}/cmake")
include(ElementsConfigCommon)
set(ELEMENTS_BUILD_EXAMPLES OFF) # 这个必须 OFF
add_subdirectory(${ELEMENTS_ROOT} elements)

# 项目
add_subdirectory(buger)
add_subdirectory(bugerw)
add_subdirectory(dbginject)
add_subdirectory(debuger)
add_subdirectory(debugere)

set_target_properties(
	buger
	bugerw
	dbginject
	debuger
	debugere
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${ALL_OUT_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${ALL_OUT_DIR}"
	RUNTIME_OUTPUT_DIRECTORY "${ALL_OUT_DIR}"
)