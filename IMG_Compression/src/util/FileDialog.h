#pragma once
#include <Windows.h>
class FileDialog
{
private:
	
public:
	LPCWSTR file_path;
	LPCWSTR OpenFile(HWND hWnd);
	void Destroy();
};

