#pragma once

#include "unipp/char_facts.hpp"

namespace unipp::detail
{
	// TODO: move `iterator_value_trait` type trait into a separate header file
	// in case it is required somewhere other than `write_char`.

	template<typename LegacyIteratorT>
	struct iterator_value_trait
	{
		using value_type = typename std::iterator_traits<LegacyIteratorT>::value_type;
	};

	template<typename ContainerT>
	struct iterator_value_trait<std::back_insert_iterator<ContainerT>>
	{
		using value_type = typename ContainerT::value_type;
	};

	template<typename ContainerT>
	struct iterator_value_trait<std::insert_iterator<ContainerT>>
	{
		using value_type = typename ContainerT::value_type;
	};

	template<typename RawT>
	struct iterator_value_trait<RawT*>
	{
		using value_type = RawT;
	};
}

namespace unipp
{
	template<
		typename OutputIterT,
		typename CodeUnitT = typename detail::iterator_value_trait<OutputIterT>::value_type
	>
	constexpr
	std::enable_if_t<std::is_same_v<CodeUnitT, char>, OutputIterT>
	write_char(code_point ch, OutputIterT out)
	{
		using facts = char_facts<CodeUnitT>;
		using code_unit = typename facts::code_unit;

		if (badchar == ch)
		{
			return out;
		}

		size_t count = facts::map_code_point_to_code_unit_count(ch);
		if (facts::invalid_code_unit_count == count)
		{
			return out;
		}

		size_t value_shift = facts::continuation_byte_significant_bit_count * (count - 1);
		char32_t value_mask = ~facts::map_code_unit_count_to_leading_byte_mask(count);

		*out = static_cast<code_unit>((ch.symbol >> value_shift) & value_mask)
			| facts::map_code_unit_count_to_leading_byte_signature(count);
		out++;

		ptrdiff_t leftover = count - 1;
		for (ptrdiff_t icontinuation = leftover - 1; icontinuation >= 0; icontinuation--)
		{
			value_shift = facts::continuation_byte_significant_bit_count * icontinuation;
			value_mask = ~facts::continuation_byte_mask;
			*out = static_cast<code_unit>((ch.symbol >> value_shift) & value_mask)
				| facts::continuation_byte_signature;
			out++;
		}

		return out;
	}

	template<
		typename OutputIterT,
		typename CodeUnitT = typename detail::iterator_value_trait<OutputIterT>::value_type
	>
	constexpr
	std::enable_if_t<std::is_same_v<CodeUnitT, char16_t>, OutputIterT>
	write_char(code_point ch, OutputIterT out)
	{
		using facts = char_facts<CodeUnitT>;
		using code_unit = typename facts::code_unit;

		if (badchar == ch)
		{
			return out;
		}

		size_t count = facts::map_code_point_to_code_unit_count(ch);
		if (facts::invalid_code_unit_count == count)
		{
			return out;
		}

		if (facts::code_unit_single == count)
		{
			*out = static_cast<code_unit>(ch.symbol);
			out++;
			return out;
		}

		char32_t cliped = ch.symbol - facts::surrogate_pair_bit_clip;

		char32_t high = cliped >> facts::code_unit_significant_bit_count
			& ~facts::high_surrogate_mask;
		char32_t low = cliped & ~facts::low_surrogate_mask;

		high += facts::high_surrogate_signature;
		low += facts::low_surrogate_signature;

		*out = high;
		out++;
		*out = low;
		out++;

		return out;
	}

	template<
		typename OutputIterT,
		typename CodeUnitT = typename detail::iterator_value_trait<OutputIterT>::value_type
	>
	constexpr
	std::enable_if_t<std::is_same_v<CodeUnitT, char32_t>, OutputIterT>
	write_char(code_point ch, OutputIterT out)
	{
		if (badchar == ch)
		{
			return out;
		}

		*out = ch.symbol;
		out++;

		return out;
	}
}

