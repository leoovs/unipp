#pragma once

#include <cstddef>

namespace unipp::experimental
{
	template<size_t WideCharSizeT = sizeof(wchar_t)>
	struct is_wchar_proxy_supported : std::bool_constant<false> {};

	template<>
	struct is_wchar_proxy_supported<sizeof(char16_t)> : std::bool_constant<true> {};

	template<>
	struct is_wchar_proxy_supported<sizeof(char32_t)> : std::bool_constant<true> {};

	constexpr bool is_wchar_proxy_supported_v = is_wchar_proxy_supported<>::value;

	using wchar_proxy_t =
		std::conditional_t<
			is_wchar_proxy_supported_v,
			std::conditional_t<
				sizeof(wchar_t) == sizeof(char16_t),
				char16_t,
				char32_t>,
			void>;
}

