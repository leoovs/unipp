#pragma once

#include "unipp/pch.hpp"
#include "unipp/char_view.hpp"

namespace unipp::detail
{
	template<typename CodeUnitT>
	struct sv_difference
	{
		using type = typename std::basic_string_view<CodeUnitT>::difference_type;
	};

	template<typename CodeUnitT>
	using sv_difference_t = typename sv_difference<CodeUnitT>::type;

	template<typename CodeUnitT>
	struct sv_size
	{
		using type = typename std::basic_string_view<CodeUnitT>::size_type;
	};

	template<typename CodeUnitT>
	using sv_size_t = typename sv_size<CodeUnitT>::type;
}

namespace unipp
{
	template<
		typename CodeUnitT,
		typename VectorAllocT = std::allocator<detail::sv_size_t<CodeUnitT>>
	>
	constexpr std::vector<detail::sv_size_t<CodeUnitT>> eachindex(
		std::basic_string_view<CodeUnitT> str,
		const VectorAllocT& alloc = VectorAllocT())
	{
		std::vector<detail::sv_size_t<CodeUnitT>> indices;
		char_view<CodeUnitT> view(str);

		detail::sv_size_t<CodeUnitT> index = 0;
		while (view.decode() != nullchar)
		{
			if (view.decode() == badchar)
			{
				return indices;
			}
			indices.push_back(index);
			index += view.get_code_unit_count();

			view = view.next();
		}

		return indices;
	}
}

