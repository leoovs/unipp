#include <iostream>

#include <unipp/char_view.hpp>
#include <unipp/write_char.hpp>

void example()
{
	std::u16string in = u"Hello, world! Привет, мир! 哈囉世界! 😊";
	std::string out; // UTF-8 assumed.

	unipp::char16_view v(in); // Iterates over UTF-16 strings.
	unipp::code_point c = v.decode(); // Stores Unicode code point value.

	while (unipp::nullchar != c)
	{
		if (unipp::invalid_char == c)
		{
			std::cerr << "Bad UTF-16 sequence!\n";
			return;
		}

		// Encodes the `c` code point as a UTF-8 character.
		unipp::write_char(c, std::back_inserter(out));
		// Move to the next character.
		c = (v = v.next()).decode();
	}

	std::cout << out << '\n';
}

int main()
{
	example();
}

