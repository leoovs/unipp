#include <iostream>

#include <unipp/codepoint.hpp>
#include <unipp/char_view.hpp>

int main()
{
	std::string msg = "Привет мир! Hello World!哈囉世界!";

	unipp::char_view<char> view(msg);
	unipp::codepoint cp = view.decode();

	while (cp != unipp::codepoint())
	{
		std::cout << cp.symbol << " - " << view.str_view() << std::endl;
		cp = (view = view.next()).decode();
	}

	return 0;
}

