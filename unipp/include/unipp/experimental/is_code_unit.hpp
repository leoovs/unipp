#pragma once

#include <type_traits>

namespace unipp::experimental
{
	template<typename CodeUnitT>
	struct is_code_unit : std::false_type {};

	template<typename CodeUnitT>
	constexpr bool is_code_unit_v = is_code_unit<CodeUnitT>::value;
}

