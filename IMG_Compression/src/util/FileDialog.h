#pragma once
#include <Windows.h>
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

