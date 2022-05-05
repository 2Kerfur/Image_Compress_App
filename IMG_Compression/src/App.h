#pragma once
#include <Windows.h>
#include <shobjidl.h> 
#include <shlobj.h> 
#include <string>
#include <gdiplus.h> //for drawing
#include <iostream>
#include <shellapi.h> //open browser
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING //filesystem fix error
#include <experimental/filesystem>

#include "gui/Gui.h" //include all gui classes (Button, Text , etc...)
#include "Log.h"

// M_ <-- means main

//main window
LPCWSTR M_window_name = L"Image Commpression App";
LPCWSTR M_window_class_name = L"WindowClass";
int M_window_width = 700;
int M_window_height = 700;

//about window
LPCWSTR Info_window_name = L"About";
LPCWSTR Info_window_class_name = L"WindowClass_2";
int Info_window_width = 350;
int Info_window_height = 350;

//settings window
LPCWSTR Settings_window_name = L"Settings";
LPCWSTR Settings_window_class_name = L"WindowClass_3";
int Settings_window_width = 500;
int Settings_window_height = 500;

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
void Info_Update(HWND hWnd);
void Info_CheckButtonInput(WPARAM wp, HWND hWnd);

void RegisterInfoWindowClass(HINSTANCE);
void CreateInfoWindow(HWND hWnd);

//info window objects
HWND Info_text_1;
HWND Info_text_2;
HWND Info_text_3;

HWND Info_Github_button;

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