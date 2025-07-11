#pragma once

#include "unipp/experimental/is_code_unit.hpp"
#include "unipp/experimental/iterator_value_type.hpp"

namespace unipp::experimental
{
	template<
		typename IteratorT,
		typename CodeUnitT = iterator_value_type_t<IteratorT>,
		typename = std::enable_if_t<is_code_unit_v<CodeUnitT>>>
	class char_view;

	template<typename IteratorT>
	char_view<IteratorT> make_char_view(IteratorT it)
	{
		return char_view<IteratorT>(it);
	}
}

