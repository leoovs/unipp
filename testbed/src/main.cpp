#include <iostream>
#include <list>

#include <unipp/write_char.hpp>
#include <unipp/experimental/char8_view.hpp>
#include <unipp/experimental/char16_view.hpp>
#include <unipp/experimental/char32_view.hpp>
#include <unipp/experimental/wchar_proxy.hpp>

int main()
{
	std::u32string names = U"𠮷野太郎";

	auto begin = std::cbegin(names);
	auto end = std::cend(names);

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

