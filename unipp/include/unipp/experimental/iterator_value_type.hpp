#pragma onc

#include <iterator>

namespace unipp::experimental
{
	template<typename IteratorT>
	struct iterator_value_type
	{
		using type = typename std::iterator_traits<IteratorT>::value_type;
	};

	template<typename ContainerT>
	struct iterator_value_type<std::insert_iterator<ContainerT>>
	{
		using type = typename ContainerT::value_type;
	};

	template<typename ContainerT>
	struct iterator_value_type<std::back_insert_iterator<ContainerT>>
	{
		using type = typename ContainerT::value_type;
	};

	template<typename IteratorT>
	using iterator_value_type_t = typename iterator_value_type<IteratorT>::type;
}

