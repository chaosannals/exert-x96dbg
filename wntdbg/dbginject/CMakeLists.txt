add_executable(dbginject)

add_dependencies(
	dbginject
	buger
	bugerw
)

target_sources(
	dbginject
	PRIVATE
	"src/main.cpp"
)