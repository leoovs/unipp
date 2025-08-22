#include <iostream>
#include <list>

#include <unipp/write_char.hpp>
#include <unipp/experimental/char8_view.hpp>
#include <unipp/experimental/char16_view.hpp>
#include <unipp/experimental/char32_view.hpp>
#include <unipp/experimental/wchar_proxy.hpp>

int main()
{
	std::wstring orig_names = L"𠮷野太郎";
	unipp::experimental::wproxystring names(orig_names.begin(), orig_names.end());

	auto begin = std::begin(names);
	auto end = std::end(names);

	unipp::experimental::char_view cv(begin, end);

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

