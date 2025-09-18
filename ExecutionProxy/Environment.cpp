#include "Environment.h"
#include <windows.h>
#include <iostream>

std::wstring GetCounterPath() {
	WCHAR buffer[MAX_PATH] = { 0 };
	ExpandEnvironmentStringsW(
		L"%programdata%\\Sony Corporation\\VAIO Gate\\",
		buffer,
		MAX_PATH
	);

	return std::wstring(buffer);
}