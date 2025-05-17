#include <iostream>
#include <memory_resource>

#include <unipp/each.hpp>

class custom_resource : std::pmr::memory_resource
{
public:
	static std::pmr::memory_resource* get()
	{
		static custom_resource instance;
		return &instance;
	}

	void* do_allocate(size_t size, size_t alignment) override
	{
		std::cout << "Allocated: " << size << " bytes\n";
		return m_upstream->allocate(size, alignment);
	}

	void do_deallocate(void* ptr, size_t size, size_t alignment) override
	{
		std::cout << "Deallocated: " << size << " bytes\n";
		return m_upstream->deallocate(ptr, size, alignment);
	}

	bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override
	{
		return this == &other;
	}

private:
	std::pmr::memory_resource* m_upstream = std::pmr::get_default_resource();
};

int main()
{
	constexpr std::string_view u8str = "Привет, мир! This is π";

	std::pmr::polymorphic_allocator<unipp::char8_view> custom_alloc(custom_resource::get());

	for (auto cv : unipp::eachchar(u8str, custom_alloc))
	{
		std::cout << cv.str_view();
	}
}

