#include <iostream>
#include <array>
#include <memory_resource>

#include <unipp/eachindex.hpp>

int main()
{
	constexpr std::string_view u8str = "Привет, мир! This is π";

	std::pmr::polymorphic_allocator<ptrdiff_t> alloc(std::pmr::get_default_resource());

	std::cout << '\'';
	for (auto i : unipp::eachindex(u8str, alloc))
	{
		std::cout << unipp::char8_view(&u8str.at(i)).str_view();
	}
	std::cout << "'\n";
}

