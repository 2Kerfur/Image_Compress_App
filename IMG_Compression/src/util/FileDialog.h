#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include <Windows.h>
#endif
class FileDialog
{
private:
	
public:
	LPCWSTR file_path;
	LPCWSTR folder_path;
	LPCWSTR OpenFile(HWND hWnd);
	LPCWSTR OpenFolder(HWND hWnd);
	void Destroy();
};

