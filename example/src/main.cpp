#ifdef _WIN32
#	include "example_win32.hpp"
#endif

#include "example_basic.hpp"
#include "example_char_view.hpp"
#include "example_iterator.hpp"

int main()
{
#ifdef _WIN32
	example_win32();
#endif // _WIN32

	example_basic();
	example_char_view();
	example_iterator();
}

