#pragma once

#include "unipp/char_view.hpp"
#include "unipp/write_char.hpp"

namespace unipp
{
	template<typename ContiguousInputIt, typename OutputIt>
	constexpr ContiguousInputIt convert(ContiguousInputIt first, ContiguousInputIt last, OutputIt dest)
	{
		using input_code_unit = typename std::iterator_traits<ContiguousInputIt>::value_type;

		ContiguousInputIt it = first;
		while (it < last)
		{
			char_view<input_code_unit> current_char_view((std::addressof(*it)));
			code_point current_decoded_char = current_char_view.decode();

			if (badchar == current_decoded_char)
			{
				return it;
			}

			dest = write_char(current_decoded_char, dest);
			std::advance(it, current_char_view.str_view().size());
		}

		return it;
	}
}

