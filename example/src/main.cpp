#include <iostream>

#include <unipp/char_view.hpp>
#include <unipp/write_char.hpp>

int main()
{
	std::u16string in = u"Привет, мир! 哈囉世界! 😊 δ";
	std::string out;

	unipp::char16_view view(in);
	unipp::code_point ch = view.decode();

	while (unipp::nullchar != ch)
	{
		unipp::write_char(ch, std::back_inserter(out));
		ch = (view = view.next()).decode();
	}

	std::cout << out << std::endl;
}

