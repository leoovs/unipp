#pragma once

#include <vector>

#include <Windows.h>

#include <unipp/convert.hpp>

inline void example_win32()
{
	std::string in = u8"Ошибка ⚠️";

	std::u16string intermediate;
	unipp::convert(in.begin(), in.end(), std::back_inserter(intermediate));

	std::vector<WCHAR> wide_buffer;
	std::copy(intermediate.begin(), intermediate.end(), std::back_inserter(wide_buffer));
	wide_buffer.push_back(L'\0');

	MessageBoxW(nullptr, wide_buffer.data(), L"Error", MB_ICONERROR);
}

