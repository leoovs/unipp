#pragma once

#include "unipp/char_view.hpp"

namespace unipp
{
	template<typename CodeUnitT>
	constexpr size_t length(std::basic_string_view<CodeUnitT> str)
	{
		size_t count = 0;
		char_view<CodeUnitT> view(str);
		while (view.decode() != nullchar)
		{
			if (view.decode() == badchar)
			{
				return count;
			}
			view = view.next();
			count++;
		}

		return count;
	}
}

