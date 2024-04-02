#pragma once

#include "unipp/char_view.hpp"

namespace unipp
{
	template<typename CodeUnitT>
	class iterator
	{
	public:
		using view = char_view<std::remove_const_t<CodeUnitT>>;

		using value_type = view;
		using reference = value_type&;

		constexpr iterator() = default;

		constexpr iterator(std::basic_string_view<CodeUnitT> character)
			: m_view(character)
		{}

		constexpr value_type operator*() const
		{
			return m_view;
		}

		constexpr iterator& operator++()
		{
			m_view = m_view.next();
			return *this;
		}

		constexpr iterator operator++(int)
		{
			iterator tmp = *this;
			++(*this);
			return tmp;
		}

		constexpr iterator& operator--()
		{
			m_view = m_view.prev();
			return *this;
		}

		constexpr iterator operator--(int)
		{
			iterator tmp = *this;
			--(*this);
			return tmp;
		}

		constexpr bool operator==(const iterator& other) const
		{
			return m_view == other.m_view;
		}

		constexpr bool operator!=(const iterator& other) const
		{
			return m_view != other.m_view;
		}

		constexpr bool operator<(const iterator& other) const
		{
			return m_view.str_view().begin() < other.m_view.str_view().begin();
		}

		constexpr bool operator<=(const iterator& other) const
		{
			return m_view.str_view().begin() <= other.m_view.str_view().begin();
		}

		constexpr bool operator>(const iterator& other) const
		{
			return m_view.str_view().begin() > other.m_view.str_view().begin();
		}

		constexpr bool operator>=(const iterator& other) const
		{
			return m_view.str_view().begin() >= other.m_view.str_view().begin();
		}

	private:
		view m_view;
	};

	template<typename ContainerT>
	constexpr auto begin(ContainerT& container)
	{
		auto it = std::begin(container);

		using code_unit = typename std::iterator_traits<decltype(it)>::value_type;

		return iterator<code_unit>(std::addressof(*it));
	}

	template<typename CodeUnitT, size_t SizeT>
	constexpr auto begin(CodeUnitT(&array)[SizeT])
	{
		auto it = std::begin(array);

		return iterator<std::remove_const_t<CodeUnitT>>(std::addressof(*it));
	}

	template<typename ContainerT>
	constexpr auto end(ContainerT& container)
	{
		auto it = std::end(container);

		using code_unit = typename std::iterator_traits<decltype(it)>::value_type;

		return iterator<code_unit>(std::addressof(*it));
	}

	template<typename CodeUnitT, size_t SizeT>
	constexpr auto end(CodeUnitT(&array)[SizeT])
	{
		auto it = std::end(array);

		return iterator<std::remove_const_t<CodeUnitT>>(std::addressof(*it));
	}
}

