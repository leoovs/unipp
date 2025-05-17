#include <iostream>

#include <unipp/length.hpp>

int main()
{
	constexpr char u8str[] = "Привет, мир! This is π";
	constexpr char16_t u16str[] = u"Привет, мир! This is π";
	constexpr char32_t u32str[] = U"Привет, мир! This is π";

	constexpr size_t u8len = unipp::length(std::string_view(u8str));
	constexpr size_t u16len = unipp::length(std::u16string_view(u16str));
	constexpr size_t u32len = unipp::length(std::u32string_view(u32str));

	std::cout << u8len << '\n'
		<< u16len << '\n'
		<< u32len << '\n';
}

