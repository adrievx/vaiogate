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

// This class is exported from the dll
class VGNET_API CVGNet {
public:
	CVGNet(void);
	// TODO: add your methods here.
};

extern VGNET_API int nVGNet;

VGNET_API int fnVGNet(void);
