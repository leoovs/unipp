#include <iostream>

#include <unipp/convert.hpp>

void example()
{
	std::u16string in = u"Hello, world! Привет, мир! 哈囉世界! 👋🌎";
	std::string out;

	// TODO: resolve issue with output iterators and back inserters.
	// Maybe introduce some kind of `unipp::output_iterator_traits` meta func.
	unipp::convert(in.begin(), in.end(), std::back_inserter(out));

	std::cout << out << " (" << out.length() << " bytes)\n";
}

int main()
{
	example();
}

