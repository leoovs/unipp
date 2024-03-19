#pragma once

#include "unipp/pch.hpp"
#include "unipp/code_point.hpp"

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

		static constexpr code_unit terminator = '\0';

		static constexpr size_t invalid_code_unit_count = 0;

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

		static constexpr size_t map_code_point_to_code_unit_count(code_point ch)
		{
			if (ch.symbol <= U'\x7F')
			{
				return 1;
			}
			else if (ch.symbol <= U'\x7FF')
			{
				return 2;
			}
			else if (ch.symbol <= U'\xFFFF')
			{
				return 3;
			}
			else if (ch.symbol <= U'\x10FFFF')
			{
				return 4;
			}

			return invalid_code_unit_count;
		}
	};

	template<>
	class char_facts<char16_t>
	{
	public:
		using code_unit = char16_t;

		static constexpr code_unit terminator = u'\0';

		static constexpr size_t invalid_code_unit_count = 0;

		static constexpr char16_t high_surrogate_mask = 0b1111110000000000;
		static constexpr char16_t high_surrogate_signature = 0b1101100000000000;

		static constexpr char16_t low_surrogate_mask = 0b1111110000000000;
		static constexpr char16_t low_surrogate_signature = 0b1101110000000000;

		static constexpr size_t code_unit_single = 1;
		static constexpr size_t code_unit_pair = 2;

		static constexpr size_t code_unit_significant_bit_count = 10;
		static constexpr char32_t surrogate_pair_bit_clip = 0x10000;

		static constexpr size_t map_code_point_to_code_unit_count(code_point ch)
		{
			if (ch.symbol < surrogate_pair_bit_clip)
			{
				return code_unit_single;
			}
			return code_unit_pair;
		}
	};
}

