#include "framework.h"
#include "ShellExtension.h"
#include "Globals.h"
#include "RegisterServer.h"

CVaioShellExtensionModule _AtlModule;

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) {
	return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

STDAPI DllCanUnloadNow() {
	return _AtlModule.DllCanUnloadNow();
}

STDAPI DllRegisterServer() {
	return _AtlModule.DllRegisterServer(TRUE);
}

STDAPI DllUnregisterServer() {
	return _AtlModule.DllUnregisterServer(TRUE);
}