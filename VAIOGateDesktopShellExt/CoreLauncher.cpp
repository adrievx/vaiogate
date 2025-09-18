#include "CoreLauncher.h"
#include "RegistryUtils.h"
#include <string>

HRESULT LaunchVaioGate(CommandInfo* cmd) {
	if (!cmd || cmd->field12 != 0) {
		return E_INVALIDARG;
	}

	if (cmd->field10 != 0) {
		return E_INVALIDARG;
	}

	HRESULT hr = S_OK;

	std::wstring exePath;
	bool result = GetVaioGateInstallPath(exePath);

	if (result) {
		wprintf(L"InstallPath: %s\n", exePath.c_str());
		ShellExecuteW(nullptr, nullptr, exePath.c_str(), L"/FromContextMenu", nullptr, SW_SHOWNORMAL);
	}
	else {
		wprintf(L"Failed to read InstallPath\n");
		hr = E_INVALIDARG;
	}

	return hr;
}