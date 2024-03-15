#pragma once

namespace unipp
{
	struct codepoint
	{
		char32_t symbol = U'\0';

		constexpr codepoint() = default;

		constexpr codepoint(char32_t symbol)
			: symbol(symbol)
		{}

		constexpr bool operator==(const codepoint& other) const
		{
			return symbol == other.symbol;
		}

		constexpr bool operator!=(const codepoint& other) const
		{
			return symbol != other.symbol;
		}
	};
}

