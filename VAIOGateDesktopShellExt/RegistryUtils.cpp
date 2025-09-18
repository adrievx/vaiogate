#include "RegistryUtils.h"

#include <windows.h>
#include <algorithm>

bool GetVaioGateInstallPath(std::wstring& outPath) {
	outPath.clear();

	constexpr LPCWSTR kRegPath = L"SOFTWARE\\Sony Corporation\\VAIO Gate";
	constexpr LPCWSTR kValueName = L"InstallPath";

	HKEY hKey = nullptr;
	LONG status = RegOpenKeyExW(HKEY_LOCAL_MACHINE, kRegPath, 0, KEY_READ | KEY_WOW64_64KEY, &hKey);
	if (status != ERROR_SUCCESS) {
		return false;
	}

	DWORD type = 0;
	DWORD sizeInBytes = 0;

	status = RegQueryValueExW(hKey, kValueName, nullptr, &type, nullptr, &sizeInBytes);
	if (status != ERROR_SUCCESS || (type != REG_SZ && type != REG_EXPAND_SZ)) {
		RegCloseKey(hKey);
		return false;
	}

	std::wstring buffer(sizeInBytes / sizeof(wchar_t), L'\0');
	status = RegQueryValueExW(hKey, kValueName, nullptr, &type, reinterpret_cast<LPBYTE>(&buffer[0]), &sizeInBytes);
	RegCloseKey(hKey);

	if (status != ERROR_SUCCESS) {
		return false;
	}

	buffer.resize(wcsnlen(buffer.c_str(), buffer.size()));

	outPath.swap(buffer);
	return true;
}
