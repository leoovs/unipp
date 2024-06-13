#pragma once

#include "unipp/char_facts.hpp"
#include "unipp/code_point.hpp"

namespace unipp::detail
{
	struct from_string_view_data_t {} inline constexpr from_string_view_data{};
}

namespace unipp
{
	template<typename CodeUnitT>
	class char_view
	{
	public:
		using facts = char_facts<CodeUnitT>;
		using code_unit = typename facts::code_unit;

		constexpr code_point decode() const = delete;
		constexpr char_view next() const = delete;
		constexpr char_view prev() const = delete;
		constexpr std::basic_string_view<CodeUnitT> str_view() const = delete;

		constexpr bool operator==(const char_view& other) const = delete;
		constexpr bool operator!=(const char_view& other) const = delete;
	};

	template<>
	class char_view<char>
	{
	public:
		using facts = char_facts<char>;
		using code_unit = typename facts::code_unit;

		constexpr char_view() = default;

		constexpr char_view(std::basic_string_view<code_unit> str)
			: char_view(str.data(), detail::from_string_view_data)
		{}

		constexpr code_point decode() const
		{
			if (facts::terminator == *m_character)
			{
				return nullchar;
			}

			if (!is_decodable())
			{
				return badchar;
			}

			code_unit value_mask = ~facts::map_code_unit_count_to_leading_byte_mask(m_code_unit_count);
			char32_t symbol = *m_character & value_mask;

			for (size_t icodeunit = 1; icodeunit < m_code_unit_count; icodeunit++)
			{
				code_unit continuation_byte = m_character[icodeunit];
				if ((continuation_byte & facts::continuation_byte_mask) != facts::continuation_byte_signature)
				{
					return badchar;
				}

				value_mask = ~facts::continuation_byte_mask;
				symbol <<= facts::continuation_byte_significant_bit_count;
				symbol |= continuation_byte & value_mask;
			}

			return code_point(symbol);
		}

		constexpr char_view next()
		{
			return char_view(m_character + m_code_unit_count);
		}

		constexpr char_view prev()
		{
			const code_unit* character = m_character;
			auto is_continuation = [&character]() constexpr
				{
					return (facts::continuation_byte_mask & *character) ==
						facts::continuation_byte_signature;
				};

			do
			{
				character--;
			} while (is_continuation());

			return char_view(character);
		}

		constexpr std::basic_string_view<code_unit> str_view() const
		{
			return std::basic_string_view<code_unit>(m_character, m_code_unit_count);
		}

		constexpr bool operator==(const char_view& other) const
		{
			return m_character == other.m_character;
		}

		constexpr bool operator!=(const char_view& other) const
		{
			return m_character != other.m_character;
		}

	private:
		constexpr char_view(const code_unit* character, detail::from_string_view_data_t)
			: m_character(character)
			, m_code_unit_count(decode_code_unit_count())
		{}

		constexpr bool is_decodable() const
		{
			return facts::invalid_code_unit_count != m_code_unit_count;
		}

		constexpr size_t decode_code_unit_count() const
		{
			if (nullptr == m_character)
			{
				return facts::invalid_code_unit_count;
			}

			code_unit leading_byte = *m_character;

			for (size_t count = facts::min_code_unit_count; count <= facts::max_code_unit_count; count++)
			{
				code_unit mask = facts::map_code_unit_count_to_leading_byte_mask(count);
				code_unit sign = facts::map_code_unit_count_to_leading_byte_signature(count);

				if ((leading_byte & mask) == sign)
				{
					return count;
				}
			}

			return facts::invalid_code_unit_count;
		}

		const code_unit* m_character = nullptr;
		size_t m_code_unit_count = facts::invalid_code_unit_count;
	};

	template<>
	class char_view<char16_t>
	{
	public:
		using facts = char_facts<char16_t>;
		using code_unit = typename facts::code_unit;

		constexpr char_view() = default;

		constexpr char_view(std::basic_string_view<code_unit> str)
			: char_view(str.data(), detail::from_string_view_data)
		{}

		constexpr code_point decode() const
		{
			if (facts::terminator == *m_character)
			{
				return nullchar;
			}

			if (!is_decodable())
			{
				return badchar;
			}

			if (facts::code_unit_single == m_code_unit_count)
			{
				return code_point(static_cast<char32_t>(get_high_surrogate()));
			}

			auto high = static_cast<char32_t>(get_high_surrogate()) & ~facts::high_surrogate_mask;
			auto low = static_cast<char32_t>(get_low_surrogate()) & ~facts::low_surrogate_mask;

			char32_t symbol = (high << facts::code_unit_significant_bit_count | low)
				+ facts::surrogate_pair_bit_clip;

			return code_point(symbol);
		}

		constexpr char_view next() const
		{
			return char_view(m_character + m_code_unit_count);
		}

		constexpr char_view prev() const
		{
			const code_unit* character = m_character - 1;

			if ((facts::low_surrogate_mask & *character) == facts::low_surrogate_signature)
			{
				character--;
			}

			return char_view(character);
		}

		constexpr std::basic_string_view<code_unit> str_view() const
		{
			return std::basic_string_view<code_unit>(m_character, m_code_unit_count);
		}

		constexpr bool operator==(const char_view& other) const
		{
			return m_character == other.m_character;
		}

		constexpr bool operator!=(const char_view& other) const
		{
			return m_character != other.m_character;
		}

	private:
		constexpr char_view(const code_unit* character, detail::from_string_view_data_t)
			: m_character(character)
			, m_code_unit_count(decode_code_unit_count())
		{}

		constexpr bool is_decodable() const
		{
			return facts::invalid_code_unit_count != m_code_unit_count;
		}

		constexpr size_t decode_code_unit_count() const
		{
			if (nullptr == m_character)
			{
				return facts::invalid_code_unit_count;
			}

			if ((get_high_surrogate() & facts::high_surrogate_mask) == facts::high_surrogate_signature)
			{
				if ((get_low_surrogate() & facts::low_surrogate_mask) == facts::low_surrogate_signature)
				{
					return facts::code_unit_pair;
				}
				return facts::invalid_code_unit_count;
			}

			return facts::code_unit_single;
		}

		constexpr char16_t get_high_surrogate() const
		{
			return m_character[0];
		}

		constexpr char16_t get_low_surrogate() const
		{
			return m_character[1];
		}

		const code_unit* m_character = nullptr;
		size_t m_code_unit_count = facts::invalid_code_unit_count;
	};

	template<>
	class char_view<char32_t>
	{
	public:
		using code_unit = char32_t;

		constexpr char_view() = default;

		constexpr char_view(std::basic_string_view<code_unit> str)
			: char_view(str.data(), detail::from_string_view_data)
		{}

		constexpr code_point decode() const
		{
			return code_point(*m_character);
		}

		constexpr char_view next() const
		{
			return char_view(m_character + 1);
		}

		constexpr char_view prev() const
		{
			return char_view(m_character - 1);
		}

		constexpr std::basic_string_view<code_unit> str_view() const
		{
			return std::basic_string_view<code_unit>(m_character, 1);
		}

		constexpr bool operator==(const char_view& other) const
		{
			return m_character == other.m_character;
		}

		constexpr bool operator!=(const char_view& other) const
		{
			return m_character != other.m_character;
		}

	private:
		constexpr char_view(const code_unit* character, detail::from_string_view_data_t)
			: m_character(character)
		{}

		const code_unit* m_character = nullptr;
	};

	using char8_view = char_view<char>;
	using char16_view = char_view<char16_t>;
	using char32_view = char_view<char32_t>;
}

