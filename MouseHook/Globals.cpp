#include "Globals.h"

HHOOK   g_hMouseHook = NULL;
HMODULE g_hModuleHandle = NULL;
HANDLE  g_hMouseMoveEvent = NULL;
HANDLE  g_hThreadHandle = NULL;
POINT   g_stPoint = { 0, 0 };
DWORD   g_lastTick = 0;
HWND    g_hWndTarget = NULL;
volatile LONG g_runTimerThread = 0;