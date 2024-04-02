#pragma once

#include <iostream>
#include <algorithm>

#include <unipp/iterator.hpp>

inline void example_iterator()
{
	const char s[] = u8"Привет, world!";

	auto begin = unipp::begin(s);
	auto end = unipp::end(s);

	std::cout << "Iterating over a string:\n";

	std::for_each(begin, --end, [](auto view)
		{
			std::cout << view.str_view() << ": " << view.decode().symbol << '\n';
		}
	);
}

