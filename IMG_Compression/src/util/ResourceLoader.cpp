#include "ResourceLoader.h"


void ResourceLoader::Init(HWND hwnd)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
}

Gdiplus::Bitmap* ResourceLoader::LoadImage(std::string fileName)
{
	WCHAR buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, sizeof(buffer) / sizeof(buffer[0]));
	std::wstring ws(buffer);
	std::string str(ws.begin(), ws.end());
	str = str.substr(0, str.find_last_of("\\/"));
	str.append("\\resources\\images\\");
	str.append(fileName);
	std::wstring temp = std::wstring(str.begin(), str.end());
	LPCWSTR file_path = temp.c_str();
	Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(file_path);

	return bitmap;
}
