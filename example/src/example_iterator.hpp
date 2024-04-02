#pragma once

#include <iostream>
#include <algorithm>

#include <unipp/iterator.hpp>

inline void example_iterator()
{
	const char16_t s[] = u"Привет, world!";

	auto begin = unipp::begin(s);
	auto end = unipp::end(s);

	std::for_each(begin, --end, [](unipp::code_point cp)
		{
			std::cout << "Iterator: " << cp.symbol << '\n';
		}
	);
}

