include(CharSet)

add_executable(unipp_testbed)
add_executable(unipp::testbed ALIAS unipp_testbed)

target_sources(
	unipp_testbed
	PRIVATE
	"src/main.cpp"
)

target_link_libraries(
	unipp_testbed
	PRIVATE
	unipp_unipp
)

set_target_properties(
	unipp_testbed
	PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED TRUE
)

enforce_msvc_utf8(unipp_testbed)

