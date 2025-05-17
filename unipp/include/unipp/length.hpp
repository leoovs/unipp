#pragma once

#include "unipp/char_view.hpp"

namespace unipp
{
	template<typename CodeUnitT>
	constexpr size_t length(char_view<CodeUnitT> view)
	{
		size_t count = 0;
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

