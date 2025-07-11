#pragma once

#include "unipp/char_facts.hpp"
#include "unipp/experimental/char_view.hpp"

namespace unipp::experimental
{
	template<typename IteratorT>
	class char_view<IteratorT, char32_t>
	{
	public:
		using iterator = IteratorT;
		using code_unit = char32_t;
		using facts = char_facts<code_unit>;

		constexpr explicit char_view(iterator begin, iterator end)
			: m_begin(begin)
			, m_end(end)
			, m_current(begin)
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

		iterator char_begin() const
		{
			return m_current;
		}

		iterator char_end() const
		{
			return std::next(m_current);
		}

		constexpr code_point decode() const
		{
			if (!is_valid())
			{
				return badchar;
			}
			return *m_current;
		}


	private:
		constexpr bool is_valid() const
		{
			return m_current != m_end;
		}

		constexpr void next_char()
		{
			std::advance(m_current, 1);
		}

		iterator m_begin = iterator();
		iterator m_end = iterator();
		iterator m_current = iterator();
	};
}

