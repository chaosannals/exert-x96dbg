﻿cmake_minimum_required(VERSION 3.24)

# https://github.com/libsdl-org/SDL

add_executable(cracksdl2 WIN32)

# SDL2
FetchContent_Declare(
	libsdl2
	# GIT_REPOSITORY git@github.com:libsdl-org/SDL.git
    # GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	# GIT_REPOSITORY https://hub.nuaa.cf/libsdl-org/SDL.git
	# GIT_TAG adf31f6ec0be0f9ba562889398f71172c7941023
	# GIT_TAG release-2.26.3
	URL https://hub.nuaa.cf/libsdl-org/SDL/releases/download/release-2.26.3/SDL2-devel-2.26.3-VC.zip
)
# FetchContent_MakeAvailable(libsdl2)
FetchContent_GetProperties(libsdl2)
if (NOT libsdl2_POPULATED)
	message(STATUS "not sdl2")
	# 二进制导入
	FetchContent_Populate(libsdl2)
	message(STATUS "sdl: ${libsdl2_SOURCE_DIR} ${libsdl2_BINARY_DIR}")

	if (${CMAKE_SIZEOF_VOID_P} EQUAL 4)
		message(STATUS "import sdl2image x86.")
		set(LIBSDL2_LIB_DIR "${libsdl2_SOURCE_DIR}/lib/x86")
	else()
		message(STATUS "import sdl2image x64.")
		set(LIBSDL2_LIB_DIR "${libsdl2_SOURCE_DIR}/lib/x64")
	endif()
	target_link_directories(
		cracksdl2
		PUBLIC
		"${LIBSDL2_LIB_DIR}"
	)
	target_include_directories(
		cracksdl2
		PUBLIC
		"${libsdl2_SOURCE_DIR}/include"
	)
	target_link_libraries(
		cracksdl2
		PRIVATE
		SDL2.lib
		SDL2main.lib
	)
	add_custom_command(
		TARGET cracksdl2 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${LIBSDL2_LIB_DIR}/SDL2.dll"
		"${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CONFIGURATION_TYPES}/SDL2.dll"
	)

	# add_subdirectory(${libsdl2_SOURCE_DIR} ${libsdl2_BINARY_DIR})
else()
	# 源码导入
	message(STATUS "has sdl2: ${libsdl2_SOURCE_DIR} ${libsdl2_BINARY_DIR}")

	# 依赖的名字由所依赖库定义不是自定义的 libsdl2 而是 SDL2,引入其他库需要自行查。
	add_dependencies(cracksdl2 SDL2)
	
	target_link_directories(
		cracksdl2
		PUBLIC
		"${libsdl2_BINARY_DIR}"
	)

	# 好像是可以创建个只是用来导入 DLL 的库，但是测了下好像无效。
	#add_library(libsdl2dll SHARED IMPORTED)
	#set_target_properties(
	#	libsdl2dll
	#	PROPERTIES
	#	IMPORTED_LOCATION "${libsdl2_BINARY_DIR}"
	#)

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_include_directories(
			cracksdl2
			PUBLIC
			"${libsdl2_BINARY_DIR}/include"
			"${libsdl2_BINARY_DIR}/include-config-debug"
		)
		add_custom_command(
			TARGET cracksdl2 POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${libsdl2_BINARY_DIR}/sdl2d.dll"
			"${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CONFIGURATION_TYPES}/sdl2d.dll"
		)
		add_custom_command(
			TARGET cracksdl2 POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${libsdl2_BINARY_DIR}/sdl2d.dll"
			"${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CONFIGURATION_TYPES}/sdl2.dll"
		)
		message(STATUS "debug link sdl2d.lib")
		target_link_libraries(
			cracksdl2
			PRIVATE
			SDL2d.lib
			SDL2maind.lib
			#SDL2test.lib
		)
	else()
		target_include_directories(
			cracksdl2
			PUBLIC
			"${libsdl2_BINARY_DIR}/include"
			# "${libsdl2_BINARY_DIR}/include-config-release"
			"${libsdl2_BINARY_DIR}/include-config-relwithdebinfo"
		)
		add_custom_command(
			TARGET cracksdl2 POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${libsdl2_BINARY_DIR}/sdl2.dll"
			"${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CONFIGURATION_TYPES}/sdl2.dll"
		)
		message(STATUS "release link sdl2.lib")
		target_link_libraries(
			cracksdl2
			PRIVATE
			SDL2.lib
			#SDL2main.lib
			#SDL2test.lib
		)
	endif()
endif()

if (TARGET SDL2)
	message(STATUS "SDL2 exists")
else()
	message(STATUS "SDL2 not exists")
endif()

if (TARGET SDL2::SDL2main)
	message(STATUS "SDL2::SDL2main exists")
else()
	message(STATUS "SDL2::SDL2main not exists")
endif()

# SDL2 Image
FetchContent_Declare(
	libsdl2image
	# GIT_REPOSITORY git@github.com:libsdl-org/SDL_image.git
	# GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
	# URL https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.3/SDL2_image-devel-2.6.3-VC.zip
	# github 网址被墙，使用镜像，如果无效，自己再找。
	URL https://hub.nuaa.cf/libsdl-org/SDL_image/releases/download/release-2.6.3/SDL2_image-devel-2.6.3-VC.zip
	# GIT_TAG d3c6d5963dbe438bcae0e2b6f3d7cfea23d02829
	# GIT_TAG release-2.6.3
)
# FetchContent_MakeAvailable(libsdl2image)
FetchContent_GetProperties(libsdl2image)
if (NOT libsdl2image_POPULATED)
	message(STATUS "not libsdl2image")
	FetchContent_Populate(libsdl2image)
	message(STATUS "libsdl2image: ${libsdl2image_SOURCE_DIR}" "${libsdl2image_BINARY_DIR}")

	# 二进制包引入
	if (${CMAKE_SIZEOF_VOID_P} EQUAL 4)
		message(STATUS "import sdl2image x86.")
		set(LIBSDL2IMAGE_LIB_DIR "${libsdl2image_SOURCE_DIR}/lib/x86")
	else()
		message(STATUS "import sdl2image x64.")
		set(LIBSDL2IMAGE_LIB_DIR "${libsdl2image_SOURCE_DIR}/lib/x64")
	endif()
	target_link_directories(
		cracksdl2
		PUBLIC
		"${LIBSDL2IMAGE_LIB_DIR}"
	)
	target_include_directories(
		cracksdl2
		PUBLIC
		"${libsdl2image_SOURCE_DIR}/include"
	)
	target_link_libraries(
		cracksdl2
		PRIVATE
		SDL2_image.lib
	)
	add_custom_command(
		TARGET cracksdl2 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${LIBSDL2IMAGE_LIB_DIR}/SDL2_image.dll"
		"${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CONFIGURATION_TYPES}/SDL2_image.dll"
	)

	# 下面是源码编译方式，有问题，找不到 SDL2 target
	# 执行命令，更新子模块，要配置代理，里面还依赖了谷歌的部分代码库，只代理GitHub不行。
	#execute_process(
	#	COMMAND git submodule update --init --recursive
    #    WORKING_DIRECTORY ${libsdl2image_SOURCE_DIR}
	#)

	# add_dependencies(libsdl2image SDL2)
	#add_subdirectory("${libsdl2image_SOURCE_DIR}" "${libsdl2image_BINARY_DIR}")

	#target_link_directories(
	#	cracksdl2
	#	PUBLIC
	#	"${libsdl2image_BINARY_DIR}"
	#)
	#target_include_directories(
	#	cracksdl2
	#	PUBLIC
	#	"${libsdl2image_BINARY_DIR}/include"
	#)
	#if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	#	message(STATUS "debug link SDL2_imaged.lib")
	#	target_link_libraries(
	#		cracksdl2
	#		PRIVATE
	#		SDL2_imaged.lib
	#	)
	#else()
	#	message(STATUS "release link SDL2_image.lib")
	#	target_link_libraries(
	#		cracksdl2
	#		PRIVATE
	#		SDL2_image.lib
	#	)
	#endif()
else()
	message(STATUS "has libsdl2image")
	message(STATUS "sdl: ${libsdl2image_SOURCE_DIR} ${libsdl2image_BINARY_DIR}")
endif()

target_sources(
	cracksdl2
	PRIVATE
	"src/main.cpp"
)

# 复制资源
add_custom_command(
	TARGET cracksdl2 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_CURRENT_SOURCE_DIR}/res"
	"${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CONFIGURATION_TYPES}/res"
)