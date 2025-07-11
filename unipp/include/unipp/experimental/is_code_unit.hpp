#pragma once

#include <type_traits>

namespace unipp::experimental
{
	template<typename CodeUnitT>
	struct is_code_unit : std::bool_constant<false> {};

	template<>
	struct is_code_unit<char> : std::bool_constant<true> {};

	template<>
	struct is_code_unit<char16_t> : std::bool_constant<true> {};

	template<>
	struct is_code_unit<char32_t> : std::bool_constant<true> {};

	template<typename CodeUnitT>
	constexpr bool is_code_unit_v = is_code_unit<CodeUnitT>::value;
}

