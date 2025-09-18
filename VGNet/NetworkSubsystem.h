#pragma once
#include "Mission.h"
#include "CriticalSectionLock.h"
#include "DownloadTask.h"

#include <windows.h>
#include <wininet.h>
#include <vector>
#include <functional>
#include <cstdint>
#include <algorithm>
#include <memory>

class NetworkSubsystem {
public:
	static NetworkSubsystem& Instance() {
		static NetworkSubsystem instance;
		return instance;
	}

	// Exported operations
	void IsInternetReady();
	void CancelMission(int64_t missionId);
	void ContinueMission();
	bool PerformHttpDownload(const wchar_t* url, void* userData);

private:
	NetworkSubsystem() {
		InitializeCriticalSection(&cs1);
		InitializeCriticalSection(&cs2);
		InitializeCriticalSection(&missionCS);

		for (int i = 0; i < 6; ++i) {
			events[i] = CreateEventW(nullptr, FALSE, FALSE, nullptr);
		}

		pauseFlag = false;

		threads[0] = threads[1] = threads[2] = nullptr;
		threadFuncs[0] = threadFuncs[1] = threadFuncs[2] = nullptr;
	}

	~NetworkSubsystem() {
		for (auto& e : events) {
			CloseHandle(e);
		}

		DeleteCriticalSection(&cs1);
		DeleteCriticalSection(&cs2);
		DeleteCriticalSection(&missionCS);
	}

	NetworkSubsystem(const NetworkSubsystem&) = delete;
	NetworkSubsystem& operator=(const NetworkSubsystem&) = delete;

	std::unique_ptr<DownloadTask> ParseUrl(const std::wstring& url, void* userData);

	void StartThread(int index, LPTHREAD_START_ROUTINE func);

	void ScheduleDownload(std::unique_ptr<DownloadTask> task);

	void SignalEvent(int index) {
		if (index >= 0 && index < 6 && events[index]) {
			SetEvent(events[index]);
		}
	}

	std::vector<std::unique_ptr<DownloadTask>> activeDownloads;
	CRITICAL_SECTION downloadListCS;
	CRITICAL_SECTION cs1;
	CRITICAL_SECTION cs2;
	CRITICAL_SECTION missionCS;

	HANDLE events[6];
	HANDLE threads[3];
	bool pauseFlag;

	Mission missions[3];

	LPTHREAD_START_ROUTINE threadFuncs[3];
};