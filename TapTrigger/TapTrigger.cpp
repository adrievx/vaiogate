#include "framework.h"
#include "TapTrigger.h"
#include "Globals.h"
#include "VGMessages.h"

#include <windows.h>
#include <vector>
#include <mutex>

void AddIgnorehWnd(HWND hWnd) {
	if (hWnd == nullptr) {
		return;
	}

	std::lock_guard<std::mutex> lock(g_ignoreMutex);

	for (HWND existing : g_ignoreHwnds) {
		if (existing == hWnd) {
			return;
		}
	}

	g_ignoreHwnds.push_back(hWnd);
}

int EndTrigger(HWND hWnd) {
	if ((hWnd == g_hTriggerHandle) || (hWnd != nullptr)) {
		SendMessageW(g_hMessageTarget, VGMSG_UNKN_0x402, 0, 0);
	}

	return 1;
}

LRESULT CALLBACK LLMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION && g_hTriggerHandle != NULL) {
		if (wParam == WM_LBUTTONDOWN || wParam == WM_NCLBUTTONDOWN) {
			MSLLHOOKSTRUCT* ms = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam);
			POINT pt = ms->pt;
			HWND hWndAtPoint = WindowFromPoint(pt);

			if (hWndAtPoint != g_hTriggerHandle && !IsChild(g_hTriggerHandle, hWndAtPoint)) {
				bool ignored = false;

				{
					std::lock_guard<std::mutex> lock(g_ignoreMutex);
					for (HWND hIgnore : g_ignoreHwnds) {
						if (hWndAtPoint == hIgnore || IsChild(hIgnore, hWndAtPoint)) {
							ignored = true;
							break;
						}
					}
				}

				if (!ignored) {
					// special shells (progman, WorkerW, SHELLDLL_DefView, SysListView32)
					HWND hProgman = FindWindowW(L"Progman", nullptr);
					HWND hDefView = (hProgman) ? FindWindowExW(hProgman, nullptr, L"SHELLDLL_DefView", nullptr) : nullptr;
					HWND hSysList = (hDefView) ? FindWindowExW(hDefView, nullptr, L"SysListView32", nullptr) : nullptr;

					bool isDesktopControl = (hWndAtPoint == hDefView) || (hWndAtPoint == hSysList);

					if (isDesktopControl) {
						PostMessageW(g_hTriggerHandle, g_customMsg, 0, 0);
					}
					else {
						PostMessageW(g_hTriggerHandle, g_customMsg, 1, 0);
					}
				}
			}
		}
	}

	return CallNextHookEx(g_hLLMouseHook, nCode, wParam, lParam);
}

BOOL StartTrigger(HWND hTarget) {
	if (g_hTriggerTarget == NULL) {
		g_hTriggerTarget = hTarget;

		// TODO: figure out the significance of this trigger
		SendMessageW(g_hTriggerWindow, WM_USER + 1, 0, 0);
	}

	return TRUE;
}

BOOL ReleaseTrigger() {
	if (g_hTriggerThread != NULL) {
		// ask trig window to quit first
		if (IsWindow(g_hTriggerWindow)) {
			PostMessageW(g_hTriggerWindow, WM_QUIT, 0, 0);
		}

		// wait
		DWORD waitResult = WaitForSingleObject(g_hTriggerThread, 500);
		if (waitResult == WAIT_TIMEOUT) {
			DWORD exitCode = 0;
			if (GetExitCodeThread(g_hTriggerThread, &exitCode)) {
				if (exitCode == STILL_ACTIVE) {
					TerminateThread(g_hTriggerThread, 0);
				}
			}
		}

		if (g_hTriggerThread != NULL) {
			CloseHandle(g_hTriggerThread);
			g_hTriggerThread = NULL;
		}

		g_hTriggerWindow = NULL;
	}

	return TRUE;
}