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

		constexpr char_view(iterator it)
			: m_leading_byte_it(it)
			, m_code_unit_count(decode_code_unit_count(*it))
		{}

		constexpr operator bool() const
		{
			return is_valid();
		}

		constexpr iterator begin() const
		{
			return m_leading_byte_it;
		}

		constexpr iterator end() const
		{
			iterator it = m_leading_byte_it;
			std::advance(it, m_code_unit_count);
			return it;
		}

		constexpr code_point decode() const
		{
			if (!is_valid())
			{
				return badchar;
			}
			if (facts::terminator == get_leading_byte())
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

		constexpr char_view next()
		{
			return char_view(end());
		}

	private:
		static constexpr int8_t decode_code_unit_count(code_unit leading_byte)
		{
			for (int8_t possible_count : facts::enumerate_code_unit_count())
			{
				if (facts::is_leading_byte_encodes_count(leading_byte, possible_count))
				{
					return possible_count;
				}
			}

			return facts::invalid_code_unit_count;
		}

		constexpr code_unit get_leading_byte() const
		{
			return *m_leading_byte_it;
		}

		constexpr bool is_valid() const
		{
			return facts::invalid_code_unit_count != m_code_unit_count;
		}

		iterator m_leading_byte_it = iterator();
		int8_t m_code_unit_count = facts::invalid_code_unit_count;
	};
}
