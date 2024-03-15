#pragma once

#include "unipp/pch.hpp"

namespace unipp
{
	template<typename CodeUnitT>
	class char_facts
	{};

	template<>
	class char_facts<char>
	{
	public:
		using code_unit = char;

		static constexpr size_t invalid_code_unit_len = 0;

		static constexpr size_t min_code_unit_count = 1;
		static constexpr size_t max_code_unit_count = 4;

		static constexpr code_unit continuation_byte_mask = 0b11000000;
		static constexpr code_unit continuation_byte_signature = 0b10000000;
		static constexpr code_unit continuation_byte_significant_bit_count = 6;

		static constexpr code_unit map_code_unit_count_to_leading_byte_mask(size_t count)
		{
			switch (count)
			{
			case 1:
				return 0b10000000;
			case 2:
				return 0b11100000;
			case 3:
				return 0b11110000;
			case 4:
				return 0b11111000;
			default:
				assert(false && "unipp: invalid code unit length");
				return 0b00000000;
			}
		}

		static constexpr code_unit map_code_unit_count_to_leading_byte_signature(size_t count)
		{
			switch (count)
			{
			case 1:
				return 0b00000000;
			case 2:
				return 0b11000000;
			case 3:
				return 0b11100000;
			case 4:
				return 0b11110000;
			default:
				assert(false && "unipp: invalid code unit length");
				return 0b11111111;
			}
		}
	};
}

