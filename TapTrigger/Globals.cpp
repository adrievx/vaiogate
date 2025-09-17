#include "Globals.h"

std::vector<HWND> g_ignoreHwnds;
std::mutex g_ignoreMutex;
HWND g_hTriggerHandle;
HWND g_hMessageTarget;
HHOOK g_hLLMouseHook;
UINT g_customMsg;
HANDLE g_hTriggerThread;
HWND g_hTriggerWindow;
HWND g_hTriggerTarget;