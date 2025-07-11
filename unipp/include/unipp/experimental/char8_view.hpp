#pragma once

#include <cstdint>

#include "unipp/char_facts.hpp"
#include "unipp/code_point.hpp"
#include "unipp/experimental/char_view.hpp"

namespace unipp::experimental
{
	template<typename IteratorT>
	class char_view<IteratorT, char>
	{
	public:
		using iterator = IteratorT;
		using code_unit = char;
		using facts = char_facts<code_unit>;

		constexpr explicit char_view(iterator begin, iterator end)
			: m_begin(begin)
			, m_end(end)
			, m_leading_byte_it(begin)
			, m_code_unit_count(decode_code_unit_count())
		{}

		constexpr explicit operator bool() const
		{
			return is_valid();
		}

		constexpr char_view operator++(int)
		{
			char_view past_me = *this;
			next_char();
			return past_me;
		}

		constexpr char_view& operator++()
		{
			next_char();
			return *this;
		}

		constexpr iterator char_begin() const
		{
			return m_leading_byte_it;
		}

		constexpr iterator char_end() const
		{
			return std::next(m_leading_byte_it, m_code_unit_count);
		}

		constexpr code_point decode() const
		{
			if (!is_valid())
			{
				return badchar;
			}
			if (facts::terminator == *m_leading_byte_it)
			{
				return nullchar;
			}

			code_point result = nullchar;

			iterator it = m_leading_byte_it;

			code_unit significant_bit_mask = ~facts::map_code_unit_count_to_leading_byte_mask(m_code_unit_count);
			result.symbol = *it & significant_bit_mask;
			++it;

			for (int8_t icode_unit = 1; icode_unit < m_code_unit_count; ++it, ++icode_unit)
			{
				code_unit continuation_byte = *it;
				if (!facts::is_continuation_byte(continuation_byte))
				{
					return badchar;
				}

				significant_bit_mask = ~facts::continuation_byte_mask;
				result.symbol <<= facts::continuation_byte_significant_bit_count;
				result.symbol |= continuation_byte & significant_bit_mask;
			}

			return result;
		}

	private:
		constexpr int8_t decode_code_unit_count() const
		{
			if (m_end == m_leading_byte_it)
			{
				return facts::invalid_code_unit_count;
			}

			for (int8_t possible_count : facts::enumerate_code_unit_count())
			{
				if (facts::is_leading_byte_encodes_count(*m_leading_byte_it, possible_count))
				{
					return possible_count;
				}
			}

			return facts::invalid_code_unit_count;
		}

		constexpr bool is_valid() const
		{
			return facts::invalid_code_unit_count != m_code_unit_count;
		}

		constexpr void next_char()
		{
			std::advance(m_leading_byte_it, m_code_unit_count);
			m_code_unit_count = decode_code_unit_count();
		}

		iterator m_begin = iterator();
		iterator m_end = iterator();
		iterator m_leading_byte_it = iterator();
		int8_t m_code_unit_count = facts::invalid_code_unit_count;
	};
}
