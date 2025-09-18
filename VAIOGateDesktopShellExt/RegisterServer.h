#pragma once
#include <windows.h>

HRESULT RegisterAppIdObjects(void* context, int commitFlag);
HRESULT ActivateAppIdObjects(void* context, int commitFlag);