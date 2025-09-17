// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the MOUSEHOOK_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// MOUSEHOOK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MOUSEHOOK_EXPORTS
#define MOUSEHOOK_API __declspec(dllexport)
#else
#define MOUSEHOOK_API __declspec(dllimport)
#endif

//extern MOUSEHOOK_API int nMouseHook;

MOUSEHOOK_API void Hook(HWND hWndTarget);
MOUSEHOOK_API void ReHook();
MOUSEHOOK_API void UnHook();