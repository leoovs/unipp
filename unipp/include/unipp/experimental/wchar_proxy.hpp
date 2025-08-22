#pragma once

#include <cstddef>
#include <cstdint>

#include <string>
#include <string_view>

namespace unipp::experimental
{
	enum class bad_wchar_proxy_t : int8_t {};

	template<size_t ProxySizeT>
	struct wchar_proxy
	{
		using type = bad_wchar_proxy_t;
	};

	template<>
	struct wchar_proxy<sizeof(char)> // Just in case...
	{
		using type = char;
	};

	template<>
	struct wchar_proxy<sizeof(char16_t)>
	{
		using type = char16_t;
	};

	template<>
	struct wchar_proxy<sizeof(char32_t)>
	{
		using type = char32_t;
	};

	using wchar_proxy_t = wchar_proxy<sizeof(wchar_t)>::type;

	using wproxystring = std::basic_string<wchar_proxy_t>;
	using wproxystring_view = std::basic_string_view<wchar_proxy_t>;

	inline constexpr bool wchar_proxy_supported_v = !std::is_same_v<
		wchar_proxy_t,
		bad_wchar_proxy_t>;
}

