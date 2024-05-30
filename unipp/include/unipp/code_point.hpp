#pragma once

namespace unipp
{
	struct code_point
	{
		char32_t symbol = U'\0';

		constexpr code_point() = default;

		constexpr code_point(char32_t symbol)
			: symbol(symbol)
		{}

		constexpr bool operator==(const code_point& other) const
		{
			return symbol == other.symbol;
		}

		constexpr bool operator!=(const code_point& other) const
		{
			return symbol != other.symbol;
		}
	};

	inline constexpr code_point nullchar = code_point(U'\x0');
	inline constexpr code_point badchar = code_point(U'\xFFFD');
}

