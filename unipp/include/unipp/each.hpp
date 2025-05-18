#pragma once

#include "unipp/pch.hpp"
#include "unipp/char_view.hpp"

namespace unipp::detail
{
	template<typename CodeUnitT>
	struct str_view_difference
	{
		using type = typename std::basic_string_view<CodeUnitT>::difference_type;
	};

	template<typename CodeUnitT>
	using str_view_difference_t = typename str_view_difference<CodeUnitT>::type;

	template<typename CodeUnitT>
	struct str_view_size
	{
		using type = typename std::basic_string_view<CodeUnitT>::size_type;
	};

	template<typename CodeUnitT>
	using str_view_size_t = typename str_view_size<CodeUnitT>::type;

	template<typename CodeUnitT>
	struct str_difference
	{
		using type = typename std::basic_string<CodeUnitT>::difference_type;
	};

	template<typename CodeUnitT>
	using str_difference_t = typename str_difference<CodeUnitT>::type;

	template<typename CodeUnitT>
	struct str_size
	{
		using type = typename std::basic_string<CodeUnitT>::size_type;
	};

	template<typename CodeUnitT>
	using str_size_t = typename str_size<CodeUnitT>::type;
}

namespace unipp
{
	template<
		typename CodeUnitT,
		typename VectorAllocT = std::allocator<detail::str_view_size_t<CodeUnitT>>
	>
	constexpr std::vector<detail::str_view_size_t<CodeUnitT>, VectorAllocT> eachindex(
		std::basic_string_view<CodeUnitT> str,
		const VectorAllocT& alloc = VectorAllocT())
	{
		using size_type = detail::str_view_size_t<CodeUnitT>;

		std::vector<size_type, VectorAllocT> indices(alloc);
		size_type index = 0;
		for (char_view<CodeUnitT> view(str); view.decode() != nullchar; view = view.next())
		{
			if (view.decode() == badchar)
			{
				return indices;
			}
			indices.push_back(index);
			index += view.get_code_unit_count();
		}

		return indices;
	}

	template<
		typename CodeUnitT,
		typename VectorAllocT = std::allocator<detail::str_size_t<CodeUnitT>>
	>
	constexpr std::vector<detail::str_size_t<CodeUnitT>, VectorAllocT> eachindex(
		const std::basic_string<CodeUnitT>& str,
		const VectorAllocT& alloc = VectorAllocT())
	{
		return eachindex(std::basic_string_view<CodeUnitT>(str), alloc);
	}

	template<
		typename CodeUnitT,
		typename VectorAllocT = std::allocator<char_view<CodeUnitT>>
	>
	constexpr std::vector<char_view<CodeUnitT>, VectorAllocT> eachchar(
		std::basic_string_view<CodeUnitT> str,
		const VectorAllocT& alloc = VectorAllocT())
	{
		std::vector<char_view<CodeUnitT>, VectorAllocT> chars(alloc);
		for (char_view<CodeUnitT> view(str); view.decode() != nullchar; view = view.next())
		{
			if (view.decode() == badchar)
			{
				return chars;
			}
			chars.push_back(view);
		}

		return chars;
	}

	template<
		typename CodeUnitT,
		typename VectorAllocT = std::allocator<char_view<CodeUnitT>>
	>
	constexpr std::vector<char_view<CodeUnitT>, VectorAllocT> eachchar(
		const std::basic_string<CodeUnitT>& str,
		const VectorAllocT& alloc = VectorAllocT())
	{
		return eachchar(std::basic_string_view<CodeUnitT>(str), alloc);
	}
}

