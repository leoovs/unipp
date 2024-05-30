#pragma once

#include <iostream>

#include <unipp/iterator.hpp>

inline void example_iterator()
{
	const char s[] = u8"Строка в UTF-8";

	auto sbegin = unipp::begin(s);
	auto send = unipp::end(s);
	send--; // TODO: set `end` to be null terminator automatically inside
					// `unipp::end` function.

	std::cout << "Length: " << std::distance(sbegin, send) << '\n';
}

