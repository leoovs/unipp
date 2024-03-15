#pragma once

#include "unipp/codepoint.hpp"
#include "unipp/char_facts.hpp"

namespace unipp
{
	template<typename CodeUnitT>
	class char_view
	{
	public:
		constexpr codepoint decode() const = delete;
		constexpr char_view next() const = delete;
		constexpr std::basic_string_view<CodeUnitT> str_view() const = delete;
	};

	template<>
	class char_view<char>
	{
	public:
		using facts = char_facts<char>;
		using code_unit = typename facts::code_unit;

		constexpr char_view() = default;

		constexpr char_view(std::basic_string_view<code_unit> str)
			: char_view(str.data(), from_string_view_data)
		{}

		constexpr codepoint decode() const
		{
			if (!able_to_decode())
			{
				return codepoint();
			}

			code_unit value_mask = ~facts::map_code_unit_count_to_leading_byte_mask(m_code_unit_count);
			char32_t symbol = *m_character & value_mask;

			for (size_t icodeunit = 1; icodeunit < m_code_unit_count; icodeunit++)
			{
				code_unit continuation_byte = m_character[icodeunit];
				if ((continuation_byte & facts::continuation_byte_mask) != facts::continuation_byte_signature)
				{
					return codepoint();
				}

				value_mask = ~facts::continuation_byte_mask;
				symbol <<= facts::continuation_byte_significant_bit_count;
				symbol |= continuation_byte & value_mask;
			}

			return codepoint(symbol);
		}

		constexpr char_view next()
		{
			return char_view(m_character + m_code_unit_count);
		}

		constexpr std::basic_string_view<code_unit> str_view() const
		{
			return std::basic_string_view<code_unit>(m_character, m_code_unit_count);
		}

	private:
		struct from_string_view_data_t {} static constexpr from_string_view_data{};

		constexpr char_view(const code_unit* character, from_string_view_data_t)
			: m_character(character)
			, m_code_unit_count(decode_code_unit_len())
		{}

		constexpr bool able_to_decode() const
		{
			return facts::invalid_code_unit_len != m_code_unit_count;
		}

		constexpr size_t decode_code_unit_len() const
		{
			if (nullptr == m_character)
			{
				return facts::invalid_code_unit_len;
			}

			code_unit leading_byte = *m_character;

			for (size_t len = facts::min_code_unit_count; len <= facts::max_code_unit_count; len++)
			{
				code_unit mask = facts::map_code_unit_count_to_leading_byte_mask(len);
				code_unit sign = facts::map_code_unit_count_to_leading_byte_signature(len);

				if ((leading_byte & mask) == sign)
				{
					return len;
				}
			}

			return facts::invalid_code_unit_len;
		}

		const code_unit* m_character = nullptr;
		size_t m_code_unit_count = facts::invalid_code_unit_len;
	};

	using char8_view = char_view<std::enable_if_t<CHAR_BIT == 8, char>>;
}

