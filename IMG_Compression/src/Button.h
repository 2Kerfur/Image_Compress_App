#pragma once
#include <Windows.h>

class Button
{
private:
	HWND button_hWnd;
public:
	HWND Create(HWND Window_hWnd, LPCWSTR Text, int ButtonID, int x_pos, int y_pos, int button_height, int button_width);
	void SetText(LPCWSTR Text);
	void Destroy();
};

