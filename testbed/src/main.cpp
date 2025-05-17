#include <iostream>

#include <unipp/length.hpp>

int main()
{
	constexpr char u8str[] = "Привет, мир! This is π";
	constexpr char16_t u16str[] = u"Привет, мир! This is π";
	constexpr char32_t u32str[] = U"Привет, мир! This is π";

	constexpr size_t u8len = unipp::length(unipp::char8_view(u8str));
	constexpr size_t u16len = unipp::length(unipp::char16_view(u16str));
	constexpr size_t u32len = unipp::length(unipp::char32_view(u32str));

	std::cout << u8len << '\n'
		<< u16len << '\n'
		<< u32len << '\n';
}

