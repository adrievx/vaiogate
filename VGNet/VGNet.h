// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the VGNET_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// VGNET_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef VGNET_EXPORTS
#define VGNET_API __declspec(dllexport)
#else
#define VGNET_API __declspec(dllimport)
#endif

#include "framework.h"
#include <cstdint>

VGNET_API void IsInternetReady();
VGNET_API void CancelMission(int64_t missionId);
VGNET_API void ContuineMission(); // should be ContinueMission but the exports are typoed in the original so its ContuineMission
VGNET_API int HttpDownload(const wchar_t* url);