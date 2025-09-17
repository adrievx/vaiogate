#include "RegistryUtils.h"

#include <windows.h>

bool GetVaioGateInstallPath(std::wstring& outPath) {
	HKEY hKey = nullptr;
	LONG status = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Sony Corporation\\VAIO Gate", 0, KEY_READ | KEY_WOW64_64KEY, &hKey);

	if (status != ERROR_SUCCESS) {
		return false;
	}

	DWORD type = 0;
	DWORD size = 0;

	status = RegQueryValueExW(hKey, L"InstallPath", nullptr, &type, nullptr, &size);
	if (status != ERROR_SUCCESS || (type != REG_SZ && type != REG_EXPAND_SZ)) {
		RegCloseKey(hKey);
		return false;
	}

	std::wstring buffer(size / sizeof(wchar_t), L'\0');

	status = RegQueryValueExW(hKey, L"InstallPath", nullptr, &type, reinterpret_cast<LPBYTE>(&buffer[0]), &size);

	RegCloseKey(hKey);

	if (status != ERROR_SUCCESS) {
		return false;
	}

	// trim
	buffer.resize(wcsnlen(buffer.c_str(), buffer.size()));

	outPath = std::move(buffer);
	return true;
}