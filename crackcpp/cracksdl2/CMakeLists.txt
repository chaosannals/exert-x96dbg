cmake_minimum_required(VERSION 3.20)

# https://github.com/libsdl-org/SDL

add_executable(cracksdl2 WIN32)

FetchContent_Declare(
	libsdl2
	GIT_REPOSITORY git@github.com:libsdl-org/SDL.git
	GIT_TAG adf31f6ec0be0f9ba562889398f71172c7941023
)

FetchContent_GetProperties(libsdl2)
if (NOT libsdl2_POPULATED)
	message(STATUS "not sdl2")
	FetchContent_Populate(libsdl2)
else()
	message(STATUS "has sdl2")
	FetchContent_MakeAvailable(libsdl2)
endif()

target_sources(
	cracksdl2
	PRIVATE
	"src/main.cpp"
)

