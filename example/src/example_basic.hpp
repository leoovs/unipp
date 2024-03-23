#pragma once

#include <iostream>

#include <unipp/convert.hpp>

inline void example_basic()
{
	std::u16string in = u"Hello, world! Привет, мир! 哈囉世界! 👋🌎";
	std::string out;

	unipp::convert(in.begin(), in.end(), std::back_inserter(out));

	std::cout << out << " (" << out.length() << ") bytes\n";
}
