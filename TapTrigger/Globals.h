#pragma once

#include <windows.h>
#include <vector>
#include <mutex>

extern std::vector<HWND> g_ignoreHwnds;
extern std::mutex        g_ignoreMutex;
extern HWND              g_hTriggerHandle;
extern HWND              g_hMessageTarget;
extern HHOOK			 g_hLLMouseHook;
extern UINT				 g_customMsg;
extern HANDLE			 g_hTriggerThread;
extern HWND			     g_hTriggerWindow;
extern HWND				 g_hTriggerTarget;