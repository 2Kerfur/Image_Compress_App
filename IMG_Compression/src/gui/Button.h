#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include <Windows.h>
#endif

class Button
{
private:
	HWND button_hWnd;
	int button_x_pos;
	int button_y_pos;
	int button_w; //button width
	int button_h; //button height
	LPCWSTR button_text;

public:
	HWND Create(HWND Window_hWnd, LPCWSTR Text, int ButtonID, int x_pos, int y_pos, int button_width, int button_height);
	void SetText(LPCWSTR Text);
	void SetSize(int button_width, int button_height);
	void SetPos(int x_pos, int y_pos);
	void SetFont(HFONT Font);
	void Destroy();
};

