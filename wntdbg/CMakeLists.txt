cmake_minimum_required(VERSION 3.24)

include(FetchContent)

set(ALL_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/all")

if (NOT WIN32)
	message(FATAL_ERROR "mast Windows.")
endif()

# elements ������
FetchContent_Declare(
    elements
    GIT_REPOSITORY git@github.com:cycfi/elements.git
    # GIT_TAG ������߲����ǩ- -
)
FetchContent_Populate(elements)
set(ELEMENTS_ROOT ${elements_SOURCE_DIR})
get_filename_component(ELEMENTS_ROOT "${ELEMENTS_ROOT}" ABSOLUTE)
set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${ELEMENTS_ROOT}/cmake")
include(ElementsConfigCommon)
set(ELEMENTS_BUILD_EXAMPLES OFF) # ������� OFF
add_subdirectory(${ELEMENTS_ROOT} elements)

# ��Ŀ
add_subdirectory(buger)
add_subdirectory(bugerw)
add_subdirectory(debuger)
add_subdirectory(debugere)

set_target_properties(
	buger
	bugerw
	debuger
	debugere
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${ALL_OUT_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${ALL_OUT_DIR}"
	RUNTIME_OUTPUT_DIRECTORY "${ALL_OUT_DIR}"
)