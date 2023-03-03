add_executable(buger)

set_target_properties(
	buger
	PROPERTIES
	CXX_STANDARD_REQUIRED ON
	CXX_STANDARD 20
)

target_sources(
	buger
	PRIVATE
	"src/main.cpp"
)