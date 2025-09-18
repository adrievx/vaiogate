#pragma once
#include <windows.h>

bool GrantFileAccess(LPWSTR filePath, LPCWSTR sidString);