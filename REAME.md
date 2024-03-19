# Uni++

A C++17 header-only UTF conversion library.

## Why another Unicode C++ library?

In my spare time I, as a crazy programming fan, do system programming.
Specifically, games. I find it very joyful to develop my own self contained
ecosystem from scratch, without relying on third parties as much as possible.
However, over the time, developing even a minimal Unicode support has become
really tedious. That's why I decided to become a third party for myself by
moving all of the Unicode support into a separate library that I can easily
copy'n'paste into any of my projects (or add it as a __CPM__ package which I
plan to support in the future). So yeah, the aim of this library is not really
to confirm to the community standards, just mine.

## Prerequisites

- A C++17 confirming compiler (tested under __MSVC__ and __MinGW__)
- CMake (optional)

## How to integrate

You can use __Uni++__ simply by copying the `unipp/include` directory contents
into your third parties folder and specifying the appropriate include directory
for the compiler.

However, __Uni++__ also integrates well with __CMake__ by providing an interface
target. Here is the basic setup script:
```CMake
add_subdirectory("unipp")

add_executable(your_target)

target_link_libraries(
    your_target
    # Usually, PUBLIC is more suitable for header-only libraries.
    PUBLIC/PRIVATE/INTERFACE
    unipp::unipp # Provides include dirs and a precompiled header file.
)
```

## How to use

Currently, all the __Uni++__ source code is `constexpr`-covered. The library
provides a simple interface for working with the UTF-encoded character sequences.
It does not dynamically allocate memory behind the scenes and it makes no use of
exceptions to report errors. The library does not introduce any specific types
to store code units, it only relies on the standard types like `char` or
`char16_t` and standard-defined semantics for those types, so you don't have to
type 'utf8' or 'utf16' everywhere (my personal preference), the only exception
is the `char` built-in type, see the __Remarks__ section below.

Here is a basic example of how one might want to use the __Uni++__ library:

```C++
#include <iostream>

#include <unipp/char_view.hpp>
#include <unipp/write_char.hpp>

void example()
{
	std::u16string in = u"Hello, world! Привет, мир! 哈囉世界! 😊";
	std::string out; // UTF-8 assumed.

	unipp::char16_view v(in); // Iterates over a UTF-16 string.
	unipp::code_point c = v.decode(); // Stores Unicode code point value.

	while (unipp::nullchar != c)
	{
		if (unipp::invalid_char == c)
		{
			std::cerr << "Bad UTF-16 sequence!\n";
			return;
		}

		// The `unipp::write_char` function understands that output iterator's
		// `container_type` stores `char`s, so it encodes the `c` code point as
		// a UTF-8 character and pushes its code units back to the `out`.
		unipp::write_char(c, std::back_inserter(out));

		// Move on to the next character.
		c = (v = v.next()).decode();
	}

	std::cout << out << '\n';
}
```

# Remarks

The `char` type assumed to be used as a code unit for UTF-8. This is due to the
lack of C++20's `char8_t` which I don't want to introduce myself as a separate
library type due to the Occam's Razor. In practice, this should not cause any
problems, since the initialization of `char[]` is allowed from the UTF-8 string
literals.

# TODO
- [ ] Source code documentation
- [ ] CMake Package Manager (CPM) support (git tags)
- [ ] Unit testing (maybe)

# Sources
- cppreference.com articles on built-in types
- Wikipedia articles on UTF-8 and UTF-16 encodings
