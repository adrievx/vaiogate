#pragma once
#include <windows.h>
#include <string>
#include <cstdint>

struct DownloadTask {
	std::wstring scheme;  // http or https
	std::wstring host;
	std::wstring path;
	uint16_t port;
	bool secure;
	HANDLE completionEvent;
};