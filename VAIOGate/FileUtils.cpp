#include "FileUtils.h"

bool EnsureDirectoriesExist(const std::wstring& path) {
	if (path.empty()) {
		return false;
	}

	size_t lastSlash = path.find_last_of(L'\\');
	if (lastSlash == std::wstring::npos) {
		return false;
	}

	size_t pos = path.find(L'\\', 0);
	if (pos != std::wstring::npos && pos > 0 && path[pos - 1] == L':') {
		pos = path.find(L'\\', pos + 1);
	}

	bool ok = true;

	while (pos != std::wstring::npos && pos < lastSlash) {
		std::wstring subdir = path.substr(0, pos);

		WIN32_FIND_DATAW findData{};
		HANDLE hFind = FindFirstFileW(subdir.c_str(), &findData);

		if (hFind == INVALID_HANDLE_VALUE || !(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			if (!CreateDirectoryW(subdir.c_str(), nullptr)) {
				DWORD err = GetLastError();
				if (err == ERROR_PATH_NOT_FOUND) {
					ok = false;
					break;
				}
			}
		}
		else {
			// exists (dir)
		}

		if (hFind != INVALID_HANDLE_VALUE) {
			FindClose(hFind);
		}

		pos = path.find(L'\\', pos + 1);
	}

	return ok;
}

void GetInstallPath(std::wstring& outPath) {
	wchar_t buffer[MAX_PATH]{};
	ExpandEnvironmentStringsW(L"%programfiles%\\Sony\\VAIO Gate\\", buffer, MAX_PATH);
	outPath.assign(buffer);
}