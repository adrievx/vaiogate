#pragma once
#include <windows.h>

extern HHOOK   g_hMouseHook;
extern HMODULE g_hModuleHandle;
extern HANDLE  g_hMouseMoveEvent;
extern HANDLE  g_hThreadHandle;
extern POINT   g_stPoint;
extern DWORD   g_lastTick;
extern HWND    g_hWndTarget;
extern volatile LONG g_runTimerThread;
