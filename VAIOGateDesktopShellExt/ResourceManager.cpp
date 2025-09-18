#include "ResourceManager.h"

HRESULT EnsureRenderingResources(VAIOContext* ctx) noexcept {
	if (ctx == nullptr) {
		return E_POINTER;
	}

	if (ctx->hImage == nullptr) {
		HMODULE hModule = _AtlBaseModule.GetModuleInstance();
		ctx->hImage = static_cast<HANDLE>(::LoadImageW(hModule, MAKEINTRESOURCEW(0xCA), IMAGE_BITMAP, 0, 0, 0x40));
	}

	constexpr LPCWSTR kEventName = L"VAIO_GATE_RENDORING_{9052E546-742F-4e41-8F92-EFF19A6EFB11}";
	HANDLE hEvent = ::OpenEventW(EVENT_ALL_ACCESS, FALSE, kEventName);
	if (hEvent != nullptr) {
		::CloseHandle(hEvent);
		return HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER);
	}

	return S_OK;
}
