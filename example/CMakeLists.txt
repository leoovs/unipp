add_executable(unipp_example)
add_executable(unipp::example ALIAS unipp_example)

target_sources(
	unipp_example
	PRIVATE
	"src/main.cpp"
)

