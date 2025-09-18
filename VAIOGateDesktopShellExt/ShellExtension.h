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

#include <atlbase.h>
#include <atlcom.h>
#include <shlobj.h>
#include <windows.h>
#include "Guids.h"
#include "resource.h"

#define SHELLEXT_DLL extern "C" 

SHELLEXT_DLL STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
SHELLEXT_DLL STDAPI DllCanUnloadNow();
SHELLEXT_DLL STDAPI DllRegisterServer();
SHELLEXT_DLL STDAPI DllUnregisterServer();
//SHELLEXT_DLL HRESULT __stdcall DllCanUnloadNow(void);

class CVaioShellExtensionModule : public ATL::CAtlDllModuleT<CVaioShellExtensionModule> {};

class ATL_NO_VTABLE CVAIOGateDesktopShellExt :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVAIOGateDesktopShellExt, &CLSID_VAIOGateDesktopShellExt>,
	public IShellExtInit,
	public IContextMenu {
public:
	CVAIOGateDesktopShellExt() {}

	DECLARE_REGISTRY_RESOURCEID(IDR_VAIOGATE_SHELLEX)
	DECLARE_NOT_AGGREGATABLE(CVAIOGateDesktopShellExt)

	BEGIN_COM_MAP(CVAIOGateDesktopShellExt)
		COM_INTERFACE_ENTRY(IShellExtInit)
		COM_INTERFACE_ENTRY(IContextMenu)
	END_COM_MAP()

	// TODO: implement IShellExtInit and IContextMenu methods here
};

extern CVaioShellExtensionModule _AtlModule;