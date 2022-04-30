#include "Log.h"

void OutputDebugString(std::string message)
{
	//convert from string to wstring
	std::wstring stemp = std::wstring(message.begin(), message.end());
	//convert from wstring to lpcwstr
	LPCWSTR sw = stemp.c_str();
	OutputDebugStringW(sw);
}