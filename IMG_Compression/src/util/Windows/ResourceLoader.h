#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include <Windows.h>
#include <string>
#include <gdiplus.h>
#endif


class ResourceLoader
{
public:
	void Init(HWND hwnd);
	Gdiplus::Bitmap* LoadImage(std::string fileName);
};

