#pragma once
#include <windows.h>
#include <atlbase.h>
#include <winerror.h>
#include "Context.h"

HRESULT EnsureRenderingResources(VAIOContext* ctx) noexcept;