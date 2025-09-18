#include "VGNet.h"
#include "NetworkSubsystem.h"

VGNET_API void IsInternetReady() {
	NetworkSubsystem::Instance().IsInternetReady();
}

VGNET_API void CancelMission(int64_t missionId) {
	NetworkSubsystem::Instance().CancelMission(missionId);
}

VGNET_API void ContuineMission() {
	NetworkSubsystem::Instance().ContinueMission();
}

int HttpDownload(const wchar_t* url) {
	return NetworkSubsystem::Instance().PerformHttpDownload(url) ? 1 : 0;
}
