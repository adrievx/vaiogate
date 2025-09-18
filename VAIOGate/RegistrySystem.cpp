#include "RegistrySystem.h"

CString GetUserGuid() {
	CString result;

	HKEY hKey;
	if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Sony Corporation\\VAIO Gate", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
		wchar_t buffer[256];
		DWORD bufferSize = sizeof(buffer);
		DWORD type = 0;

		if (RegQueryValueExW(hKey, L"UserGUID", nullptr,
			&type, reinterpret_cast<LPBYTE>(buffer),
			&bufferSize) == ERROR_SUCCESS &&
			type == REG_SZ) {
			result = buffer;
		}

		RegCloseKey(hKey);
	}

	return result;
}

void InitRegistryContext() {}
void CloseRegistryContext() {}

bool WriteRegistryDWORD(HKEY root, LPCWSTR subKey, LPCWSTR valueName) {
	HKEY hKey = nullptr;
	bool success = false;

	LSTATUS status = RegCreateKeyExW(root, subKey, 0, nullptr, 0, KEY_ALL_ACCESS, nullptr, &hKey, nullptr);

	if (status == ERROR_SUCCESS) {
		DWORD data = 1;
		status = RegSetValueExW(hKey, valueName, 0, REG_DWORD, reinterpret_cast<const BYTE*>(&data), sizeof(data));
		success = (status == ERROR_SUCCESS);
		RegCloseKey(hKey);
	}

	return success;
}

DWORD ReadRegistryDWORD(HKEY root, LPCWSTR subKey, LPCWSTR valueName) {
	HKEY hKey = nullptr;
	DWORD value = 0;
	DWORD type = 0;
	DWORD dataSize = sizeof(value);

	if (RegOpenKeyExW(root, subKey, 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS) {
		if (RegQueryValueExW(hKey, valueName, nullptr, &type, reinterpret_cast<LPBYTE>(&value), &dataSize) == ERROR_SUCCESS && type == REG_DWORD) {
			// value is now valid
		}

		RegCloseKey(hKey);
	}

	return value;
}

void EnsureRegistryKeyExists(HKEY root, LPCWSTR subKey, LPCWSTR valueName) {
	HKEY hKey = nullptr;
	HKEY hSub = nullptr;

	if (RegCreateKeyExW(root, subKey, 0, nullptr, 0, KEY_WRITE | KEY_QUERY_VALUE, nullptr, &hKey, nullptr) == ERROR_SUCCESS) {
		RegCreateKeyExW(hKey, valueName, 0, nullptr, 0, KEY_WRITE | KEY_QUERY_VALUE, nullptr, &hSub, nullptr);

		if (hSub) {
			RegCloseKey(hSub);
		}

		RegCloseKey(hKey);
	}
}

// ----- //

void SaveVGRegistryValue(CStringW& valueName) {
	LPCWSTR name = valueName.GetString();

	InitRegistryContext();
	WriteRegistryDWORD(HKEY_CURRENT_USER, L"Software\\Sony Corporation\\VAIO Gate", name);
	CloseRegistryContext();

	valueName.Empty();
}

DWORD GetVGRegistryValue(CStringW& valueName) {
	LPCWSTR name = valueName.GetString();

	InitRegistryContext();
	DWORD result = ReadRegistryDWORD(HKEY_CURRENT_USER, L"Software\\Sony Corporation\\VAIO Gate", name);
	CloseRegistryContext();

	valueName.Empty();
	return result;
}

DWORD GetStyleFlag() {
	InitRegistryContext();
	DWORD result = ReadRegistryDWORD(HKEY_LOCAL_MACHINE, L"Software\\Sony Corporation\\VAIO Gate", L"StyleFlag");
	CloseRegistryContext();

	return result;
}

void EnsureMainItemsKey() {
	InitRegistryContext();
	EnsureRegistryKeyExists(HKEY_CURRENT_USER, L"Software\\Sony Corporation\\VAIO Gate", L"MainItems");
	CloseRegistryContext();
}

DWORD GetMainItemsRegistryValue() {
	InitRegistryContext();

	DWORD result = ReadRegistryDWORD(HKEY_CURRENT_USER, L"Software\\Sony Corporation\\VAIO Gate", L"MainItems");

	CloseRegistryContext();
	return result;
}
