include(ExternalProject)

#set(CMAKE_FIND_DEBUG_MODE 1)

# 设置在顶层cmakelists.txt 无效，要紧接 fetchcontent
set(BUILD_EXAMPLES OFF)
set(BUILD_TESTING OFF)
message(STATUS "prefix: ${CMAKE_INSTALL_PREFIX}  src: ${CMAKE_CURRENT_SOURCE_DIR}")

#ExternalProject_Add(
    #Libssh2
    #GIT_REPOSITORY git@github.com:libssh2/libssh2.git
    #GIT_TAG libssh2-1.10.0
	#BUILD_ALWAYS 1
	# STEP_TARGETS build
	# CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
    # INSTALL_COMMAND "${CMAKE_COMMAND}" --build . --target INSTALL --config ${CMAKE_BUILD_TYPE}
#)

FetchContent_Declare(
	libssh2
	GIT_REPOSITORY git@github.com:libssh2/libssh2.git
	GIT_TAG libssh2-1.10.0
)
#FetchContent_Populate(libssh2)
#add_subdirectory("${libssh2_SOURCE_DIR}" "${libssh2_BINARY_DIR}" EXCLUDE_FROM_ALL)
FetchContent_MakeAvailable(libssh2)

message(STATUS "[libssh2] type: ${CMAKE_BUILD_TYPE} src: ${libssh2_SOURCE_DIR} bin: ${libssh2_BINARY_DIR}")
execute_process(
	COMMAND ${CMAKE_COMMAND} .
	WORKING_DIRECTORY "${libssh2_SOURCE_DIR}"
)
execute_process(
	COMMAND ${CMAKE_COMMAND} --build . --config ${CMAKE_BUILD_TYPE}
	WORKING_DIRECTORY "${libssh2_SOURCE_DIR}"
)
execute_process(
	COMMAND ${CMAKE_COMMAND} --install . --config ${CMAKE_BUILD_TYPE} --prefix "${libssh2_BINARY_DIR}"
	WORKING_DIRECTORY "${libssh2_SOURCE_DIR}"
)

add_executable(crackssh2)

target_include_directories(
	crackssh2
	PRIVATE 
	"${libssh2_BINARY_DIR}/include"
)

target_link_directories(
	crackssh2
	PRIVATE
	"${libssh2_BINARY_DIR}/lib"
)

target_link_libraries(
	crackssh2
	PRIVATE
	libssh2
)

# find_package(Libssh2 REQUIRED CONFIG) # 这个很容易找到 VCPKG 的包，然后就很怪。
# target_link_libraries(crackssh2 Libssh2::libssh2)
target_sources(
	crackssh2
	PRIVATE
	"src/main.cpp"
)