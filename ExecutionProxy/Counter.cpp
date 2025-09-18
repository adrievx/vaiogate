#include "Counter.h"
#include "Environment.h"

#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>

void StartCounter() {
	std::wstring counterFile = GetCounterPath() + L"VGCounter.txt";

	DWORD attributes = GetFileAttributesW(counterFile.c_str());
	if (attributes == INVALID_FILE_ATTRIBUTES) {
		std::ofstream ofs(counterFile);
		if (ofs) {
			ofs << 1;
			std::wcout << L"VGCounter.txt created and set to 1.\n";
		}
		else {
			std::wcerr << L"Failed to create VGCounter.txt\n";
		}
	}
	else {
		std::ifstream ifs(counterFile);
		int value = 0;
		if (ifs) {
			ifs >> value;
			ifs.close();
		}

		value++;

		std::ofstream ofs(counterFile, std::ios::trunc);
		if (ofs) {
			ofs << value;
			std::wcout << L"VGCounter.txt incremented to " << value << L".\n";
		}
		else {
			std::wcerr << L"Failed to write VGCounter.txt\n";
		}
	}
}

void EndCounter() {
	std::wcout << L"Ending counter.\n";
}
