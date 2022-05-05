#pragma once
#include <Windows.h>
#include <string>
#include <gdiplus.h> //for drawing
#include <iostream>
#include <shellapi.h> //open browser

#include "gui/Gui.h" //include all gui classes (Button, Text , etc...)
#include "util/Log.h"
#include "util/FileDialog.h"

// M_ <-- means main

//TODO: organize this structures better create one structure or create "window class"
struct MAIN_WINDOW {
    LPCWSTR name = L"Image Commpression App";
    LPCWSTR class_name = L"WindowClass";
    int width = 700;
    int height = 700;
} Main_Window;

struct INFO_WINDOW {
    LPCWSTR name = L"About";
    LPCWSTR class_name = L"WindowClass_2";
    int width = 350;
    int height = 350;
} Info_Window;

struct SETTINGS_WINDOW {
    LPCWSTR name = L"Settings";
    LPCWSTR class_name = L"WindowClass_3";
    int width = 500;
    int height = 500;
} Settings_Window;


//logic image vars
LPCWSTR image_path;
bool image_opened = false;

//program state
int program_state = 0; //set default program state
#define NOFILE_OPENED 0
#define IMAGE_OPENED 1
#define FOLDER_OPENED 2

//toolbar state
#define M_MENU_ID_OPEN_FILE 1
#define M_MENU_ID_OPEN_FOLDER 2
#define M_MENU_ID_EXIT 3
#define M_MENU_ID_APP_INFO 4
#define M_MENU_ID_SETTINGS 6

//tools menu
void M_CheckToolbarInput(WPARAM, HWND);
void M_AddToolbar(HWND);
void M_Menu_Open_File(HWND); // HDC
void M_Menu_Open_Folder(HWND);
void M_Menu_Exit(HWND);
void M_Menu_App_Info(HWND);

HMENU MainToolbar;
HMENU ChildFileMenu;
HMENU ChildAboutMenu;
//other
void M_AddGUI(HWND);
void M_Update(HWND hWnd);
void M_CreatePopupMenuOnCursor(HWND hWnd);
void M_Draw(HDC hdc);
int RegisterMWindowClass(HINSTANCE hInst);
void CreateMWindow();


//INFO window
#define INFO_BUTTON_GIT 5

void Info_AddGUI(HWND hWnd);
void Info_CheckButtonInput(WPARAM wp, HWND hWnd);

void RegisterInfoWindowClass(HINSTANCE);
void CreateInfoWindow(HWND hWnd);

//Settings window
void RegisterSettingsWindowClass(HINSTANCE);
void CreateSettingsWindow(HWND hWnd);

void Settings_AddGUI(HWND hWnd);
void Settings_Update(HWND hWnd);
void Settings_CheckButtonInput(WPARAM wp, HWND hWnd);

//window procedures callbacks
LRESULT CALLBACK M_WindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Info_WindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Settings_WindowProcedure(HWND, UINT, WPARAM, LPARAM);