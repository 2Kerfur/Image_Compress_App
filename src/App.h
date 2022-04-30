#pragma once
#include <Windows.h>
#include <shobjidl.h> 
#include <shlobj.h> 
#include <sstream>
#include <string>

#include "Log.h"
//vars
LPCWSTR M_window_name = L"Image Commpression App";
LPCWSTR M_window_class_name = L"WindowClass";
int window_width = 500;
int window_height = 500;

#define MENU_ID_OPEN_FILE 1
#define MENU_ID_OPEN_FOLDER 2
#define MENU_ID_EXIT 3
#define MENU_ID_APP_INFO 4

void CheckToolbarInput(WPARAM wp, HWND hWnd);
void AddToolbar(HWND);

void Menu_Open_File(HWND hWnd);
void Menu_Open_Folder();
void Menu_Exit();
void Menu_App_Info();

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);