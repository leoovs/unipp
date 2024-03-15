add_executable(unipp_example)
add_executable(unipp::example ALIAS unipp_example)

target_sources(
	unipp_example
	PRIVATE
	"src/main.cpp"
)

target_link_libraries(
	unipp_example
	PRIVATE
	unipp_unipp
)

set_target_properties(
	unipp_example
	PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED TRUE
)

