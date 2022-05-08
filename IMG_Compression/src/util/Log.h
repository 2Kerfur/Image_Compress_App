#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include <iostream>
#endif

void OutputDebugString(std::string string);

#define APP_LOG(...)		    OutputDebugString(__VA_ARGS__)
