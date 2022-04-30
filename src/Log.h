#pragma once
#include <Windows.h>
#include <iostream>

void OutputDebugString(std::string string);

#define APP_LOG(...)		    OutputDebugStringW(__VA_ARGS__)
