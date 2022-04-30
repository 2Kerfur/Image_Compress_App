#include "App.h"


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	WNDCLASSW wc = {0};

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = M_window_class_name;
	wc.lpfnWndProc = WindowProcedure;
	
	if (!RegisterClassW(&wc))
		return -1;

	CreateWindowW(M_window_class_name, M_window_name,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, window_width,
		window_height, NULL, NULL, NULL, NULL); //create window from window class

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		CheckToolbarInput(wp, hWnd);
		break;
	case WM_CREATE:
		AddToolbar(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); //makes GetMessage define result False
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void CheckToolbarInput(WPARAM wp, HWND hWnd)
{
	switch (wp)
	{
	case MENU_ID_OPEN_FILE:
		Menu_Open_File(hWnd);
		break;
	case MENU_ID_OPEN_FOLDER:
		Menu_Open_Folder();
		break;
	case MENU_ID_EXIT:
		Menu_Exit();
		break;
	case MENU_ID_APP_INFO:
		Menu_App_Info();
		break;
	}
}

void Menu_Open_File(HWND hWnd)
{
	APP_LOG("Menu Open File\n");
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileOpen;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			// Show the Open dialog box.
			hr = pFileOpen->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						APP_LOG(pszFilePath);
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
}

void Menu_Open_Folder()
{
	APP_LOG("Menu Open Folder\n");
}

void Menu_Exit()
{
	APP_LOG("Menu Exit\n");
	PostQuitMessage(0);
}

void Menu_App_Info()
{
	APP_LOG("Menu App Info\n");
}

void AddToolbar(HWND hWnd)
{
	HMENU MainToolbar = CreateMenu();
	HMENU ChildFileMenu = CreateMenu();
	HMENU ChildAboutMenu = CreateMenu();
	AppendMenu(MainToolbar, MF_POPUP, (UINT_PTR)ChildFileMenu, L"File");
		AppendMenu(ChildFileMenu, MF_STRING, MENU_ID_OPEN_FILE, L"Open File");
		AppendMenu(ChildFileMenu, MF_STRING, MENU_ID_OPEN_FOLDER, L"Open Folder");
		AppendMenu(ChildFileMenu, MF_STRING, MENU_ID_EXIT, L"Exit");

	AppendMenu(MainToolbar, MF_POPUP, (UINT_PTR)ChildAboutMenu, L"About");
		AppendMenu(ChildAboutMenu, MF_STRING, MENU_ID_APP_INFO, L"App Info");
	
	SetMenu(hWnd, MainToolbar);
}