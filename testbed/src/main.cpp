#include "unipp/char_view.hpp"
#include <iostream>
#include <list>

#include <unipp/experimental/char8_view.hpp>

int main()
{
	const char names[]
	{
		'\xE6','\x95','\xB0', // 数
		'\xE5','\xAD','\x97', // 字
		'\xE9','\xAB','\x98', // 高
		'\xE7','\xA8','\x8B', // 程
		'\xE6','\xA8','\xA1', // 模
		'\xE5','\x9E','\x8B', // 型

		'\x20', // <Space>

		'\xD0', '\x9B', // Л
		'\xD0', '\xB5', // е
		'\xD0', '\xBE', // о
		'\xD0', '\xBD', // н
		'\xD0', '\xB8', // и
		'\xD0', '\xB4', // д
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

		std::cout << std::hex << sym << ": '" << std::string(cv.char_begin(), cv.char_end())
			<< "'\n";
	}
}

