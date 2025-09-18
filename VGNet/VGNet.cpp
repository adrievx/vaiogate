// VGNet.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "VGNet.h"


// This is an example of an exported variable
VGNET_API int nVGNet=0;

// This is an example of an exported function.
VGNET_API int fnVGNet(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CVGNet::CVGNet()
{
    return;
}
