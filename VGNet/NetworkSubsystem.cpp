#include "NetworkSubsystem.h"

#include <cstring>
#include <iostream>
#include <mutex>

#pragma comment(lib, "wininet.lib")

void NetworkSubsystem::IsInternetReady() {
	DWORD flags = 0;
	wchar_t desc[260] = { 0 };
	InternetGetConnectedStateExW(&flags, desc, _countof(desc), 0);
}

void NetworkSubsystem::CancelMission(int64_t missionId) {
	CriticalSectionLock lock(cs2);

	for (int i = 0; i < 3; ++i) {
		if (missions[i].enabled && missions[i].id == missionId) {
			StartThread(i, threadFuncs[i]);
		}
	}
}

void NetworkSubsystem::ContinueMission() {
	pauseFlag = false;

	for (int i = 0; i < 3; ++i) {
		if (missions[i].enabled) {
			StartThread(i, threadFuncs[i]);
		}
	}

	SignalEvent(0);
}

bool NetworkSubsystem::PerformHttpDownload(const wchar_t* url, void* userData) {
	auto task = ParseUrl(url, userData);
	if (!task) return false;

	ScheduleDownload(std::move(task));
	return true;
}

std::unique_ptr<DownloadTask> NetworkSubsystem::ParseUrl(const std::wstring& url, void* userData) {
	auto task = std::make_unique<DownloadTask>();
	//task->userData = userData;
	task->completionEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
	task->port = 0;
	task->secure = false;

	std::wstring::size_type schemeEnd = url.find(L"://");
	if (schemeEnd == std::wstring::npos) {
		return nullptr; // invalid URL
	}

	task->scheme = url.substr(0, schemeEnd);
	task->secure = (_wcsicmp(task->scheme.c_str(), L"https") == 0);

	std::wstring remainder = url.substr(schemeEnd + 3);
	std::wstring::size_type pathStart = remainder.find(L'/');
	std::wstring hostPort = remainder.substr(0, pathStart);
	task->path = (pathStart != std::wstring::npos) ? remainder.substr(pathStart) : L"/";

	std::wstring::size_type colonPos = hostPort.find(L':');
	if (colonPos != std::wstring::npos) {
		task->host = hostPort.substr(0, colonPos);
		task->port = static_cast<uint16_t>(std::stoi(hostPort.substr(colonPos + 1)));
	}
	else {
		task->host = hostPort;
		task->port = task->secure ? 443 : 80;
	}

	return task;
}

void NetworkSubsystem::StartThread(int index, LPTHREAD_START_ROUTINE func) {
	if (index < 0 || index >= 3 || func == nullptr) {
		return;
	}

	CriticalSectionLock lock(cs2); // lock RAII

	if (!threads[index]) {
		threads[index] = CreateThread(nullptr, 0, func, this, 0, nullptr);
	}
	else {
		DWORD wait = WaitForSingleObject(threads[index], 0);
		if (wait != 0) {
			threads[index] = CreateThread(nullptr, 0, func, this, 0, nullptr);
		}
	}

	if (index + 1 < 6 && events[index + 1]) {
		SetEvent(events[index + 1]);
	}
}

void NetworkSubsystem::ScheduleDownload(std::unique_ptr<DownloadTask> task) {
	CriticalSectionLock lock(downloadListCS);
	activeDownloads.push_back(std::move(task));
}
