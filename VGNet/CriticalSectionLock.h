#pragma once
#include <windows.h>
#include <wininet.h>
#include <vector>
#include <functional>
#include <cstdint>

class CriticalSectionLock {
	CRITICAL_SECTION& cs;
public:
	explicit CriticalSectionLock(CRITICAL_SECTION& cs_) : cs(cs_) {
		EnterCriticalSection(&cs);
	}
	~CriticalSectionLock() {
		LeaveCriticalSection(&cs);
	}

	CriticalSectionLock(const CriticalSectionLock&) = delete;
	CriticalSectionLock& operator=(const CriticalSectionLock&) = delete;
};
