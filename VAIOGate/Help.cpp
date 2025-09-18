#include "Help.h"
#include "FileUtils.h"

#include <windows.h>
#include <shlwapi.h>
#include <htmlhelp.h>
#include <string>

#pragma comment(lib, "htmlhelp.lib")
#pragma comment(lib, "shlwapi.lib")

void ShowHelp(DWORD_PTR contextId) {
	std::wstring path;
	GetInstallPath(path);

	wchar_t langBuffer[32]{};
	int len = LoadStringW(GetModuleHandleW(nullptr), 0x834, langBuffer, 32);
	if (len == 0) {
		path += L"EN-US";
	}
	else {
		path += langBuffer;
	}

	path += L"\\VAIO Gate.chm";

	if (!path.empty()) {
		HWND hwndHelp = nullptr;
		if (contextId != 0) {
			hwndHelp = HtmlHelpW(nullptr, path.c_str(), HH_HELP_CONTEXT, contextId);
		}
		if (!hwndHelp) {
			HtmlHelpW(nullptr, path.c_str(), HH_DISPLAY_TOPIC, 0);
		}
	}
}