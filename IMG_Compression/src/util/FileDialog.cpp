#include "FileDialog.h"
#include <string>
#include <shobjidl.h> 
#include <shlobj.h> 
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING //filesystem fix error
#include <experimental/filesystem>

LPCWSTR FileDialog::OpenFile(HWND hWnd)
{
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
							file_path = pszFilePath;

							return file_path;
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
	file_path = L"NoFile";
	return file_path;
}

