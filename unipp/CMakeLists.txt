add_library(unipp_unipp INTERFACE)
add_library(unipp::unipp ALIAS unipp_unipp)

target_include_directories(
	unipp_unipp
	INTERFACE
	"include"
)

target_precompile_headers(
	unipp_unipp
	INTERFACE
	"include/unipp/pch.hpp"
)

