#include "App.h" //430

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	//Init GDI+
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	
	//register and create windows
	if (!RegisterMWindowClass(hInst)) { return -1; }
	RegisterInfoWindowClass(hInst);
	RegisterSettingsWindowClass(hInst);

	CreateMWindow();
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}

void M_Update(HWND hWnd) {
	
}

void M_AddGUI(HWND hWnd)
{
	//LPCWSTR filename = L"D:\\DEV\\c++\\IMG_Compression\\Release\\resources\\example.png";
	////const char* filename = "D:\\DEV\\c++\\IMG_Compression\\Release\\resources\\example.png";
	//HBITMAP bmp = (HBITMAP)LoadImage(NULL, filename,
	//	IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	//hWnd, L"hi", NULL, 200, 200, 50, 100
	Button button;
	button.Create(hWnd, L"Convert", NULL, 200, 200, 50, 100);
	button.SetSize(100, 100);
	button.SetPos(0, 0);
}

void M_CreatePopupMenuOnCursor(HWND hWnd) //for future dev
{
	POINT cp;
	GetCursorPos(&cp);
	HMENU hPopupMenu = CreatePopupMenu();
	InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, NULL, L"Fullscreen");
	InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, NULL, L"Save");
	InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, NULL, L"Save As");
	InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, NULL, L"Delete");

	SetForegroundWindow(hWnd);
	TrackPopupMenu(hPopupMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, cp.x, cp.y, 0, hWnd, NULL);
}

void M_Draw(HDC hdc) {
	Gdiplus::Graphics gf(hdc);
	
	switch (program_state) 
	{
	case NOFILE_OPENED:
	{
		WCHAR buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, sizeof(buffer) / sizeof(buffer[0]));
		std::wstring ws(buffer);
		std::string str(ws.begin(), ws.end());
		str = str.substr(0, str.find_last_of("\\/"));
		str.append("\\resources\\drag_and_drop.png");
		std::wstring temp = std::wstring(str.begin(), str.end());
		LPCWSTR file_path = temp.c_str();
		Gdiplus::Bitmap cat_bmp(file_path);
		gf.DrawImage(&cat_bmp, 264, 0);
		APP_LOG("NOFILE_OPENED\n");
		break;	
	}
	case IMAGE_OPENED:
	{
		Gdiplus::Bitmap example_bmp(image_path);
		gf.DrawImage(&example_bmp, 264, 0);
		break;
	}
	case FOLDER_OPENED:
		break;
	}

	
}

//toolbar
void M_AddToolbar(HWND hWnd)
{
	MainToolbar = CreateMenu();
	ChildFileMenu = CreateMenu();
	ChildAboutMenu  = CreateMenu();
	AppendMenu(MainToolbar, MF_POPUP, (UINT_PTR)ChildFileMenu, L"File");
	AppendMenu(ChildFileMenu, MF_STRING, M_MENU_ID_OPEN_FILE, L"Open File");
	AppendMenu(ChildFileMenu, MF_STRING, M_MENU_ID_OPEN_FOLDER, L"Open Folder");
	AppendMenu(ChildFileMenu, MF_STRING, M_MENU_ID_EXIT, L"Exit");

	AppendMenu(MainToolbar, MF_POPUP, (UINT_PTR)ChildAboutMenu, L"About");
	AppendMenu(ChildAboutMenu, MF_STRING, M_MENU_ID_APP_INFO, L"App Info");

	AppendMenu(MainToolbar, MF_STRING, M_MENU_ID_SETTINGS, L"Settings");
	
	SetMenu(hWnd, MainToolbar);
}

void M_CheckToolbarInput(WPARAM wp, HWND hWnd)
{
	switch (wp)
	{
	case M_MENU_ID_OPEN_FILE:
		M_Menu_Open_File(hWnd);
		break;
	case M_MENU_ID_OPEN_FOLDER:
		M_Menu_Open_Folder(hWnd);
		break;
	case M_MENU_ID_EXIT:
		M_Menu_Exit(hWnd);
		break;
	case M_MENU_ID_APP_INFO:
		M_Menu_App_Info(hWnd);
		break;
	case M_MENU_ID_SETTINGS:
		CreateSettingsWindow(hWnd);
		break;
	}
	
}

void M_Menu_Open_File(HWND hWnd)
{
	APP_LOG("Menu Open File Dialog\n");
	PWSTR pszFilePath;
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileOpen;
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
		if (SUCCEEDED(hr))
		{
			hr = pFileOpen->Show(NULL); // Show the Open dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
					if (SUCCEEDED(hr))
					{
						CoTaskMemFree(pszFilePath);

						namespace fs = std::experimental::filesystem;
						fs::path filePath = pszFilePath;
						if (filePath.extension() == ".jpg")
						{
							image_path = pszFilePath;
							program_state = IMAGE_OPENED;
							RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
						}
						else
						{
							fs::path f_name_p = filePath.extension();
							std::string f_name = f_name_p.filename().string();
							std::wstring wstr(f_name.begin(), f_name.end());
							std::wstring concatted_stdstr = L"Application does not support " + wstr;
							LPCWSTR concatted = concatted_stdstr.c_str();
							int ErrorBox = MessageBox(
								hWnd,
								(LPCWSTR)concatted,
								(LPCWSTR)L"Error",
								MB_ICONERROR
							);
						}
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
}

void M_Menu_Open_Folder(HWND hWnd)
{
	APP_LOG("Menu Open Folder\n");

}

void M_Menu_Exit(HWND hWnd)
{
	APP_LOG("Menu Exit\n");
	PostQuitMessage(0);
}

void M_Menu_App_Info(HWND hWnd)
{
	CreateInfoWindow(hWnd);
}
//toolbar ----

//info window --
void RegisterInfoWindowClass(HINSTANCE hInst) {
	WNDCLASSW dialog = { 0 };
	dialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
	dialog.hCursor = LoadCursor(NULL, IDC_ARROW);
	dialog.hInstance = hInst;
	dialog.lpszClassName = Info_window_class_name;
	dialog.lpfnWndProc = Info_WindowProcedure;
	dialog.hIcon = (HICON)LoadImage(NULL, L"resources/question.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE | LR_DEFAULTSIZE);

	RegisterClassW(&dialog);
}
void CreateInfoWindow(HWND hWnd)
{
	CreateWindowW(Info_window_class_name, Info_window_name, 
		WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION |
		WS_SYSMENU | WS_MINIMIZEBOX,
		500, 500, Info_window_width, Info_window_height, 
		hWnd, NULL, NULL, NULL);
}
//info window --

//main window --
int RegisterMWindowClass(HINSTANCE hInst)
{
	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = M_window_class_name;
	wc.lpfnWndProc = M_WindowProcedure;
	wc.hIcon = (HICON)LoadImage(NULL, L"resources/icon.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	if (!RegisterClassW(&wc))
		return 1;
}
void CreateMWindow()
{
	CreateWindowW(M_window_class_name, M_window_name,
		WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 100, 100, M_window_width,
		M_window_height, NULL, NULL, NULL, NULL); //create window from window class
}
//main window --

//settings window --
void RegisterSettingsWindowClass(HINSTANCE hInst)
{
	WNDCLASSW dialog_1 = { 0 };
	dialog_1.hbrBackground = (HBRUSH)COLOR_WINDOW;
	dialog_1.hCursor = LoadCursor(NULL, IDC_ARROW);
	dialog_1.hInstance = hInst;
	dialog_1.lpszClassName = Settings_window_class_name;
	dialog_1.lpfnWndProc = Settings_WindowProcedure;
	dialog_1.hIcon = (HICON)LoadImage(NULL, L"resources/question.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	RegisterClassW(&dialog_1);
}

void CreateSettingsWindow(HWND hWnd)
{
	CreateWindowW(Settings_window_class_name, Settings_window_name,
		WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 500, 500, Settings_window_width,
		Settings_window_height, hWnd, NULL, NULL, NULL);
}
//settings window --
void Info_CheckButtonInput(WPARAM wp, HWND hWnd) {
	
	switch (wp)
	{
	case INFO_BUTTON_GIT:
		ShellExecute(0, 0, L"http://github.com/2Kerfur/Image_Compress_App", 0, 0, SW_SHOW);
		break;
	}

}

void Info_Update(HWND hWnd)
{
	
}
void Info_AddGUI(HWND hWnd)
{
	HFONT SegoeFont = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	Text text_1, text_2, text_3;
	Button Github_button;
	text_1.Create(hWnd, L"This program created for jpg image compression", NULL, 10, 10, 350, 100, SegoeFont);
	text_2.Create(hWnd, L"Program support .jpg files only", NULL, 10, 35, 350, 100, SegoeFont);
	text_3.Create(hWnd, L"Developed by: 2Kefur", NULL, 100, 255, 180, 180, SegoeFont);
	Github_button.Create(hWnd, L"GITHUB", INFO_BUTTON_GIT, 130, 280, 70, 20);
	Github_button.SetFont(SegoeFont);
}

void Settings_Update(HWND hWnd)
{

}

void Settings_CheckButtonInput(WPARAM wp, HWND hWnd)
{
}
void Settings_AddGUI(HWND hWnd)
{
	auto hFont = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	Text text_1;
	text_1.Create(hWnd, L"Image Save Path: ", NULL, 10, 10, 350, 100, NULL);
	HWND hwndEdit = CreateWindowEx(
		0, L"EDIT",   // predefined class 
		NULL,         // no window title 
		WS_CHILD | WS_VISIBLE | WS_VSCROLL |
		ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
		120, 10, 200, 20,   // set size in WM_SIZE message 
		hWnd,         // parent window 
		NULL,   // edit control ID 
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL);        // pointer not needed

}

//procedures ---
LRESULT CALLBACK M_WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (msg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		M_Draw(hdc); //draw
		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
		M_CheckToolbarInput(wp, hWnd);
		M_Update(hWnd);
		break;
	case WM_CREATE:
		M_AddToolbar(hWnd);
		M_AddGUI(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_RBUTTONDOWN:
		M_CreatePopupMenuOnCursor(hWnd);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

LRESULT CALLBACK Info_WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
		Info_CheckButtonInput(wp, hWnd);
		Info_Update(hWnd);
		break;
	case WM_CREATE:
		Info_AddGUI(hWnd);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

LRESULT CALLBACK Settings_WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
		break;
	case WM_CREATE:
		Settings_AddGUI(hWnd);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}
//procedures ---
