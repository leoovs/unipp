#include "unipp/char_view.hpp"
#include <iostream>
#include <list>

#include <unipp/write_char.hpp>
#include <unipp/experimental/char8_view.hpp>
#include <unipp/experimental/char16_view.hpp>

int main()
{
	const char16_t names[]
	{
		u'\xD842', u'\xDFB7', // 𠮷
		u'\x91CE',            // 野
		u'\x592A',            // 太
		u'\x90CE',            // 郎
	};

	auto begin = std::cbegin(names);
	auto end = std::end(names);

	auto cv = unipp::experimental::make_char_view(begin, end);

	for (; cv.char_begin() != end; cv++)
	{
		if (!cv)
		{
			std::cerr << "BAD CHAR\n";
			break;
		}

		unipp::code_point cp = cv.decode();
		char32_t sym = cp.symbol;

		std::string repr;
		unipp::write_char(cp, std::back_inserter(repr));

		std::cout << std::hex << sym << ": '" << repr << "'\n";
	}
}

