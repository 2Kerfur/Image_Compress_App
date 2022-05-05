#pragma once
#include <Windows.h>

class Text
{
private:
	int text_x_pos;
	int text_y_pos;
	int text_w; //button width
	int text_h; //button height
	LPCWSTR text_text;
public:
	HWND hWnd;
	HWND Create(HWND Window_hWnd, LPCWSTR Text, int TextID, int x_pos, int y_pos, int text_width, int text_height);
	void SetText(LPCWSTR Text);
	void SetSize(int button_width, int button_height);
	void SetPos(int x_pos, int y_pos);
	void SetFont(HFONT Font);
	void Destroy();
};

