#pragma once
#include <windows.h>
#include <string>

bool EnsureDirectoriesExist(const std::wstring& path);
void GetInstallPath(std::wstring& outPath);