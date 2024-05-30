#pragma once

#include <iostream>

#include <unipp/iterator.hpp>

inline void example_iterator()
{
	const char s[] = u8"Hello world";

	auto sbegin = unipp::begin(s);
	auto send = unipp::end(s);
	send--; // TODO: set `end` to be null terminator automatically inside
					// `unipp::end` function.

	// Expectd output:
	// Length: 30
	std::cout << "Length: " << std::distance(sbegin, send) << '\n';
}

