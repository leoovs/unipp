#pragma once

#include "unipp/char_view.hpp"
#include "unipp/write_char.hpp"

namespace unipp
{
	template<typename ContiguousInputIt, typename OutputIt>
	constexpr OutputIt convert(ContiguousInputIt first, ContiguousInputIt last, OutputIt dest_first)
	{
		using input_code_unit = typename std::iterator_traits<ContiguousInputIt>::value_type;

		ContiguousInputIt it = first;
		while (it < last)
		{
			char_view<input_code_unit> view((std::addressof(*it)));
			dest_first = write_char(view.decode(), dest_first);
			std::advance(it, view.str_view().size());
		}

		return dest_first;
	}
}

