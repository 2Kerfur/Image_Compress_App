#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H
#include <Windows.h>
#endif

class Text
{
private:
	int text_x_pos;
	int text_y_pos;
	int text_w; //button width
	int text_h; //button height
	LPCWSTR text_text;
	
	
public:
	HWND Text_hWnd;
	HWND Window_hWnd;
	
	HWND Create(HWND Window_hWnd, LPCWSTR Text, int TextID, int x_pos, int y_pos, int text_width, int text_height, HFONT font);
	void SetText(LPCWSTR Text);
	void SetSize(int button_width, int button_height);
	void SetPos(int x_pos, int y_pos);
	void SetFont(HFONT Font);
	void Destroy();
};

