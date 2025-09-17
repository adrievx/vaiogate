// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the VAIOGATEDESKTOPSHELLEXT_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// SHELLEXT_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef VAIOGATEDESKTOPSHELLEXT_EXPORTS
#define SHELLEXT_API __declspec(dllexport)
#else
#define SHELLEXT_API __declspec(dllimport)
#endif

// This class is exported from the dll
class SHELLEXT_API CVAIOGateDesktopShellExt {
public:
	CVAIOGateDesktopShellExt(void);
	// TODO: add your methods here.
};

extern SHELLEXT_API int nVAIOGateDesktopShellExt;

SHELLEXT_API int fnVAIOGateDesktopShellExt(void);
