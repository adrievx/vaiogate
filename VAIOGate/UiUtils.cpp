#include "UiUtils.h"

#include <shlwapi.h>
#include <shlobj.h>
#include <shobjidl.h>
#include <shellapi.h>
#include <commctrl.h>
#include <shobjidl.h>
#include <commoncontrols.h>

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "shell32.lib")

EXTERN_C const IID IID_IImageList = { 0x46EB5926,0x582E,0x4017,{0x9F,0xDF,0xE8,0x99,0x8D,0xAA,0x09,0x50} }; // TODO: figure out if this is correct

HICON ResolveFileIcon(CString path, UINT size) {
	HICON hIcon = nullptr;
	int iconIndex = -1;

	if (!PathFileExistsW(path)) {
		return nullptr;
	}

	CString lowerPath = path;
	lowerPath.MakeLower();
	if (lowerPath.Right(4) == L".exe") {
		iconIndex = 0;
	}

	if (iconIndex == -1) {
		WCHAR iconLocation[MAX_PATH];
		DWORD sizeBuf = MAX_PATH;
		if (AssocQueryStringW(0, ASSOCSTR_DEFAULTICON, path, L"open",
			iconLocation, &sizeBuf) == S_OK) {
			
			WCHAR* context = nullptr;
			WCHAR* token = wcstok_s(iconLocation, L",", &context);
			if (token) {
				CString expanded;
				ExpandEnvironmentStringsW(token, expanded.GetBuffer(MAX_PATH), MAX_PATH);
				expanded.ReleaseBuffer();
				path = expanded;

				token = wcstok_s(nullptr, L",", &context);
				if (token) {
					iconIndex = _wtoi(token);
				}
			}
		}
	}

	if (lowerPath.Find(L"shell32.dll") != -1) {
		IImageList* pImageList = nullptr;
		HRESULT hr = SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, (void**)&pImageList);
		if (SUCCEEDED(hr) && pImageList) {
			HICON hIcon = nullptr;
			int idx = Shell_GetCachedImageIndexW(path, iconIndex, 0);
			pImageList->GetIcon(idx, ILD_NORMAL, &hIcon);
			pImageList->Release();
		}
	}

	if (!hIcon) {
		UINT tmp = 0;
		PrivateExtractIconsW(path, iconIndex, size, size, &hIcon, &tmp, 1, 0);
	}

	if (!hIcon) {
		SHFILEINFOW sfi = { 0 };
		SHGetFileInfoW(path, 0, &sfi, sizeof(sfi), SHGFI_ICON);
		hIcon = sfi.hIcon;
	}

	return hIcon;
}
