// ExecutionProxy.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ExecutionProxy.h"
#include <shellapi.h>
#include "Counter.h"

#include <string>
#include <vector>
#include <iostream>

#define MAX_LOADSTRING 100

HINSTANCE g_hInstance = nullptr;
UINT g_exitCode = 0;

void Initialize();
void ParseCommandLine();
void RegisterAppWindowClass();
void ProcessCommand(const std::wstring& arg, bool isOption, bool isLast);
std::wstring LoadStringResource(UINT id, size_t bufferSize = 100);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
	g_hInstance = hInstance;

	Initialize();
	ParseCommandLine();

	return g_exitCode;
}

void Initialize() {
	RegisterAppWindowClass();
}

void ParseCommandLine() {
	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	if (!argv) {
		return;
	}

	for (int i = 1; i < argc; ++i) {
		std::wstring arg = argv[i];
		bool isOption = false;

		if (!arg.empty() && (arg[0] == L'-' || arg[0] == L'/')) {
			isOption = true;
			arg = arg.substr(1);
		}

		bool isLast = (i + 1 == argc);
		ProcessCommand(arg, isOption, isLast);
	}

	LocalFree(argv);
}

void RegisterAppWindowClass() {
	WNDCLASSEXW wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEXW);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = DefWindowProcW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = g_hInstance;
	wcex.hIcon = LoadIconW(g_hInstance, MAKEINTRESOURCE(107));
	wcex.hCursor = nullptr;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = LoadStringResource(IDS_APP_TITLE).c_str();
	wcex.hIconSm = LoadIconW(g_hInstance, MAKEINTRESOURCE(107));

	RegisterClassExW(&wcex);
}

void ProcessCommand(const std::wstring& arg, bool isOption, bool isLast) {
	if (!isOption) {
		if (arg == L"EndCounter") {
			EndCounter();
		}
	}
	else {
		if (arg == L"StartCounter") {
			StartCounter();
		}
	}

	if (isLast) {
		g_exitCode = 0;
	}
}

std::wstring LoadStringResource(UINT id, size_t bufferSize) {
	std::wstring buffer(bufferSize, L'\0');
	LoadStringW(g_hInstance, id, &buffer[0], static_cast<int>(bufferSize));
	buffer.resize(wcslen(buffer.c_str()));
	return buffer;
}