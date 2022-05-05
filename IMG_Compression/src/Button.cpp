#include "Button.h"
#include <Windows.h>
#include <iostream>
#include <ShlObj.h>

HWND Button::Create(HWND Window_hWnd, LPCWSTR Text, int ButtonID, int x_pos, int y_pos, int button_width, int button_height)
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
	button_x_pos = x_pos;
	button_y_pos = y_pos;
	button_w = button_width;
	button_h = button_height;

	button_text = Text;
	return button_hWnd;
}

void Button::SetPos(int x_pos, int y_pos)
{
	button_x_pos = x_pos;
	button_y_pos = y_pos;
	SetWindowPos(button_hWnd, 0, x_pos, y_pos, button_w, button_h, SWP_SHOWWINDOW);
}

void Button::SetSize(int button_width, int button_height)
{
	button_w = button_width;
	button_h = button_height;
	SetWindowPos(button_hWnd, 0, button_x_pos, button_y_pos, button_width, button_height, SWP_SHOWWINDOW | SWP_NOMOVE);
	
}
void Button::SetText(LPCWSTR Text)
{
	button_text = Text;
	SendMessage(button_hWnd, WM_SETTEXT, 0,(LPARAM)Text);
}

void Button::SetFont(HFONT Font)
{
	SendMessage(button_hWnd, WM_SETFONT, WPARAM(Font), TRUE);
}

void Button::Destroy()
{
	DestroyWindow(button_hWnd);
}
