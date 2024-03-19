#pragma once

#include "unipp/char_facts.hpp"

namespace unipp
{
	template<
		typename OutputIterT,
		typename OutputT = typename OutputIterT::container_type::value_type
	>
	constexpr
	std::enable_if_t<std::is_same_v<OutputT, char>, bool>
	write_char(code_point ch, OutputIterT out)
	{
		using facts = char_facts<OutputT>;
		using code_unit = typename facts::code_unit;

		if (invalid_char == ch)
		{
			return false;
		}

		size_t octets = facts::map_code_point_to_code_unit_count(ch);
		if (facts::invalid_code_unit_count == octets)
		{
			return false;
		}

		size_t value_shift = facts::continuation_byte_significant_bit_count * (octets - 1);
		char32_t value_mask = ~facts::map_code_unit_count_to_leading_byte_mask(octets);

		out = static_cast<code_unit>((ch.symbol >> value_shift) & value_mask)
			| facts::map_code_unit_count_to_leading_byte_signature(octets);

		ptrdiff_t leftover = octets - 1;
		for (ptrdiff_t ioctet = leftover - 1; ioctet >= 0; ioctet--)
		{
			value_shift = facts::continuation_byte_significant_bit_count * ioctet;
			value_mask = ~facts::continuation_byte_mask;
			out = static_cast<code_unit>((ch.symbol >> value_shift) & value_mask)
				| facts::continuation_byte_signature;
		}

		return true;
	}

	template<
		typename OutputIterT,
		typename OutputT = typename OutputIterT::container_type::value_type
	>
	constexpr
	std::enable_if_t<std::is_same_v<OutputT, char16_t>, bool>
	write_char(code_point ch, OutputIterT out)
	{
		using facts = char_facts<OutputT>;
		using code_unit = typename facts::code_unit;

		if (invalid_char == ch)
		{
			return false;
		}

		size_t count = facts::map_code_point_to_code_unit_count(ch);

		if (facts::code_unit_single == count)
		{
			out = static_cast<code_unit>(ch.symbol);
			return true;
		}

		char32_t cliped = ch.symbol - facts::surrogate_pair_bit_clip;

		char32_t high = cliped >> facts::code_unit_significant_bit_count
			& ~facts::high_surrogate_mask;
		char32_t low = cliped & ~facts::low_surrogate_mask;

		high += facts::high_surrogate_signature;
		low += facts::low_surrogate_signature;

		out = high;
		out = low;

		return true;
	}
}

