#pragma once

#include <iostream>

#include "unipp/char_view.hpp"

inline void example_char_view()
{
	char s[] = u8"Строчка со смайлами 😊👋";
	const char* nullterm = s + std::size(s) - 1;
	unipp::char8_view view(nullterm);

	while (view.str_view().data() != s)
	{
		view = view.prev();
		std::cout << "Code point: " << view.decode().symbol << '\n';
	}
}


