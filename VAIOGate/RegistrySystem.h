#pragma once
#include <windows.h>
#include <atlstr.h>

CString GetUserGuid();
void SaveVGRegistryValue(CStringW& valueName);
DWORD GetVGRegistryValue(CStringW& valueName);
DWORD GetStyleFlag();
void EnsureMainItemsKey();
DWORD GetMainItemsRegistryValue();