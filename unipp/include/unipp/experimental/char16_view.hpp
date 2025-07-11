#pragma once

#include <cstdint>

#include "unipp/char_facts.hpp"
#include "unipp/experimental/char_view.hpp"

namespace unipp::experimental
{
	template<typename IteratorT>
	class char_view<IteratorT, char16_t>
	{
	public:
		using iterator = IteratorT;
		using code_unit = char16_t;
		using facts = char_facts<code_unit>;

		constexpr char_view(iterator begin, iterator end)
			: m_begin(begin)
			, m_end(end)
			, m_current(begin)
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
			return m_current;
		}

		constexpr iterator char_end() const
		{
			return std::next(m_current, m_code_unit_count);
		}

		constexpr code_point decode() const
		{
			if (!is_valid())
			{
				return badchar;
			}
			if (facts::terminator == *m_current)
			{
				return nullchar;
			}
			if (facts::code_unit_single == m_code_unit_count)
			{
				return code_point(static_cast<char32_t>(*m_current));
			}

			auto high_significant_bits = static_cast<char32_t>(*m_current)
				& ~facts::high_surrogate_mask;
			auto low_significant_bits = static_cast<char32_t>(*std::next(m_current))
				& ~facts::low_surrogate_mask;

			char32_t symbol = (high_significant_bits
					<< facts::code_unit_significant_bit_count
					| low_significant_bits)
					+ facts::surrogate_pair_bit_clip;

			return code_point(symbol);
		}

	private:
		constexpr int8_t decode_code_unit_count() const
		{
			if (m_current == m_end)
			{
				return facts::invalid_code_unit_count;
			}

			code_unit potential_high_surrogate = *m_current;

			if (facts::is_high_surrogate(potential_high_surrogate))
			{
				code_unit potential_low_surrogate = *std::next(m_current);
				if (facts::is_low_surrogate(potential_low_surrogate))
				{
					return facts::code_unit_pair;
				}
				return facts::invalid_code_unit_count;
			}

			return facts::code_unit_single;
		}

		constexpr bool is_valid() const
		{
			return facts::invalid_code_unit_count != m_code_unit_count;
		}

		constexpr void next_char()
		{
			std::advance(m_current, m_code_unit_count);
			m_code_unit_count = decode_code_unit_count();
		}

		iterator m_begin = iterator();
		iterator m_end = iterator();
		iterator m_current = iterator();
		int8_t m_code_unit_count = facts::invalid_code_unit_count;
	};
}

