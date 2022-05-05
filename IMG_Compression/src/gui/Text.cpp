#include "Text.h"
#include <Windows.h>
#include <iostream>
#include <ShlObj.h>

HWND Text::Create(HWND Window_hWnd, LPCWSTR Text, int TextID, int x_pos, int y_pos, int text_width, int text_height, HFONT font)
{
    // TODO:Add more text styles
    Text_hWnd = CreateWindowW(L"static", Text,
        WS_VISIBLE | WS_CHILD, 
        x_pos, // x position
        y_pos, // y position
        text_width, //text width
        text_height, // text height
        Window_hWnd, //parent window hwnd
        (HMENU)TextID, //text id
        NULL, 
        NULL);
    if (font != NULL)
    {
        SendMessage(Text_hWnd, WM_SETFONT, WPARAM(font), TRUE);
    }

    return Text_hWnd;
}

void Text::SetText(LPCWSTR Text)
{
    text_text = Text;
    SendMessage(Text_hWnd, WM_SETTEXT, 0, (LPARAM)Text);
}

void Text::SetSize(int text_width, int text_height)
{
    text_w = text_width;
    text_h = text_height;
    SetWindowPos(Text_hWnd, 0, text_x_pos, text_y_pos,
        text_width, 
        text_height, 
        SWP_SHOWWINDOW | SWP_NOMOVE);
}

void Text::SetPos(int x_pos, int y_pos)
{
    text_x_pos = x_pos;
    text_y_pos = y_pos;
    SetWindowPos(Text_hWnd, 0,
        x_pos, 
        y_pos, 
        text_w, text_h, SWP_SHOWWINDOW);
}

void Text::SetFont(HFONT Font)
{
    SendMessage(Text_hWnd, WM_SETFONT, WPARAM(Font), TRUE);
}

void Text::Destroy()
{
    DestroyWindow(Text_hWnd);
}
