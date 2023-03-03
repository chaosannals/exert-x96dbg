add_executable(debuger)

add_dependencies(
	debuger
	buger
	bugerw
)

target_sources(
	debuger
	PRIVATE
	"src/main.cpp"
)