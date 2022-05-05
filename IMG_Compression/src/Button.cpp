#include "Button.h"
#include <Windows.h>
#include <iostream>

HWND Button::Create(HWND Window_hWnd, LPCWSTR Text, int ButtonID, int x_pos, int y_pos, int button_height, int button_width)
{
	button_hWnd = CreateWindowW(L"BUTTON", Text,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		x_pos,         // x position 
		y_pos,         // y position 
		button_width,        // Button width
		button_height,        // Button height
		Window_hWnd,     // Parent window
		(HMENU)ButtonID,
		NULL,
		NULL);
	return button_hWnd;
}

void Button::SetText(LPCWSTR Text)
{
	SendMessage(button_hWnd, WM_SETTEXT, 0,(LPARAM)Text);
}

void Button::Destroy()
{
	DestroyWindow(button_hWnd);
}
