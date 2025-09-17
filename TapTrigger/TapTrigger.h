// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the TAPTRIGGER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// TAPTRIGGER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TAPTRIGGER_EXPORTS
#define TAPTRIGGER_API __declspec(dllexport)
#else
#define TAPTRIGGER_API __declspec(dllimport)
#endif

//extern TAPTRIGGER_API int nTapTrigger;

//TAPTRIGGER_API int fnTapTrigger(void);
TAPTRIGGER_API void AddIgnorehWnd(HWND hWnd);
TAPTRIGGER_API int EndTrigger(HWND hWnd);

extern "C" TAPTRIGGER_API BOOL ReleaseTrigger();
extern "C" TAPTRIGGER_API LRESULT CALLBACK LLMouseProc(int nCode, WPARAM wParam,LPARAM lParam);
extern "C" TAPTRIGGER_API BOOL StartTrigger(HWND hTarget);