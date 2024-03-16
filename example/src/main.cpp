#include <iostream>

#include <unipp/char_view.hpp>

void u8_example()
{
	std::string msg = "Привет мир! 哈囉世界!"
	// "\xff\xff\xff\xff" // bad code unit sequence.
	;

	unipp::char8_view view(msg);
	unipp::code_point cp = view.decode();

	while (unipp::nullchar != cp)
	{
		if (unipp::invalid_char == cp)
		{
			std::cout << "Bad UTF-8 code unit sequence!\n";
			break;
		}

		std::cout << cp.symbol << '\n';
		cp = (view = view.next()).decode();
	}
}

void u16_example()
{
	std::u16string msg = u"Привет мир! 哈囉世界! \xD800\xffff";

	unipp::char16_view view(msg);
	unipp::code_point cp = view.decode();

	while (cp != unipp::nullchar)
	{
		if (cp == unipp::invalid_char)
		{
			std::cout << "Bad UTF-16 code unit sequence!\n";
			break;
		}

		std::cout << cp.symbol << std::endl;
		cp = (view = view.next()).decode();
	}
}

int main()
{
	u8_example();
	u16_example();
}

