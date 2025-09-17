#include "framework.h"
#include "MouseHook.h"

#include "Globals.h"

extern LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);
DWORD WINAPI MouseTimerThreadProc(LPVOID lpParam);

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0) {
		MOUSEHOOKSTRUCT* pMouse = reinterpret_cast<MOUSEHOOKSTRUCT*>(lParam);

		switch (wParam) {
		case WM_MOUSEMOVE:
			g_stPoint = pMouse->pt;

			if (g_hMouseMoveEvent != NULL) {
				SetEvent(g_hMouseMoveEvent);
			}

			break;

		default:			
			break;
		}
	}

	return CallNextHookEx(g_hMouseHook, nCode, wParam, lParam);
}

DWORD WINAPI MouseTimerThreadProc(LPVOID lpParam) {
	HANDLE hWaitableTimer = NULL;
	HANDLE handles[2] = { NULL, NULL };
	LARGE_INTEGER dueTime;
	DWORD waitResult;

	UNREFERENCED_PARAMETER(lpParam);

	hWaitableTimer = CreateWaitableTimerW(nullptr, FALSE, nullptr);
	if (hWaitableTimer == NULL) {
		// failed to create timer, exit thread
		return GetLastError();
	}

	handles[0] = g_hMouseMoveEvent;
	handles[1] = hWaitableTimer;

	g_lastTick = GetTickCount();

	while (InterlockedCompareExchange(&g_runTimerThread, g_runTimerThread, g_runTimerThread) != 0) {
		waitResult = WaitForMultipleObjects(2, handles, FALSE, INFINITE);

		// handles[0] signalled goign to mouse move event
		if (waitResult == WAIT_OBJECT_0) {
			DWORD now = GetTickCount();
			DWORD delta = (now >= g_lastTick) ? (now - g_lastTick) : 0xFFFFFFFF;

			// TODO: possibly make this better
			if (delta != 0xFFFFFFFF && delta < 0x29) {
				LONGLONG relative100ns = static_cast<LONGLONG>((static_cast<int>(delta) - 0x28) * 10000LL);
				dueTime.QuadPart = relative100ns;
			}
			else {
				dueTime.QuadPart = 0;
			}

			SetWaitableTimer(hWaitableTimer, &dueTime, 0, nullptr, nullptr, FALSE);
		}
		else if (waitResult == WAIT_OBJECT_0 + 1) { // handles[1] signalled to timer fired
			if (g_hWndTarget != NULL) {
				PostMessageW(g_hWndTarget, 0x9000, 0, 0);
			}

			g_lastTick = GetTickCount();
		}
		else if (waitResult == WAIT_FAILED) {
			break;
		}
		else if (waitResult == WAIT_ABANDONED_0 || waitResult == WAIT_ABANDONED_0 + 1) {
			break;
		}
	}

	if (hWaitableTimer != NULL) {
		CancelWaitableTimer(hWaitableTimer);
		CloseHandle(hWaitableTimer);
		hWaitableTimer = NULL;
	}

	if (g_hThreadHandle != NULL) {
		CloseHandle(g_hThreadHandle);
		g_hThreadHandle = NULL;
	}

	return 0;
}

void Hook(HWND hWndTarget) {
	g_hWndTarget = hWndTarget;

	if (g_hMouseMoveEvent == NULL) {
		g_hMouseMoveEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
	}

	if (g_hThreadHandle == NULL && g_hMouseMoveEvent != NULL) {
		g_runTimerThread = 1;

		g_hThreadHandle = CreateThread(nullptr, 0, MouseTimerThreadProc, nullptr, 0, nullptr);
	}

	if (g_hMouseHook == NULL) {
		g_hMouseHook = SetWindowsHookExW(WH_MOUSE, MouseHookProc, g_hModuleHandle, 0);
	}
}

void ReHook() {
	if (g_hMouseHook != NULL) {
		UnhookWindowsHookEx(g_hMouseHook);
		g_hMouseHook = NULL;
	}

	g_hMouseHook = SetWindowsHookExW(WH_MOUSE, MouseHookProc, g_hModuleHandle, 0);
}

void UnHook() {
	if (g_hMouseHook != NULL) {
		if (UnhookWindowsHookEx(g_hMouseHook)) {
			g_hMouseHook = NULL;
		}
	}

	if (g_hMouseMoveEvent != NULL) {
		SetEvent(g_hMouseMoveEvent);
		CloseHandle(g_hMouseMoveEvent);
		g_hMouseMoveEvent = NULL;
	}

	if (g_hThreadHandle != NULL) {
		g_runTimerThread = 0;

		DWORD waitResult = WaitForSingleObject(g_hThreadHandle, 100);

		if (waitResult == WAIT_TIMEOUT) {
			TerminateThread(g_hThreadHandle, 0);
		}

		CloseHandle(g_hThreadHandle);
		g_hThreadHandle = NULL;
	}
}