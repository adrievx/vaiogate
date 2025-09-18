#pragma once
#include <windows.h>

UINT g_vaioGateCloseMsg = 0;
UINT g_vaioGateLaunchKbMsg = 0;
UINT g_vaioGateLaunchRemoteControlMsg = 0;
UINT g_vaioGateLaunchSecondMsg = 0;
UINT g_vaioGateOpenHelpFileMsg = 0;
UINT g_vaioGatePressEscMsg = 0;
UINT g_vaioGateAddFeedMsg = 0;
UINT g_vaioGateFeedUpdateCompletedMsg = 0;
UINT g_vaioGateItemLoadedMsg = 0;
UINT g_changeEditMsg = 0;
UINT g_drawFromEditMsg = 0;
UINT g_deleteChannelMsg = 0;
UINT g_renameChannelMsg = 0;
UINT g_channelClickMsg = 0;

void RegisterVaioGateCloseMessage();
void RegisterVaioGateLaunchKbMessage();
void RegisterVaioGateLaunchRemoteControlMessage();
void RegisterVaioGateLaunchSecondMessage();
void RegisterVaioGateOpenHelpFileMessage();
void RegisterVaioGatePressEscMessage();
void RegisterVaioGateAddFeedMessage();
void RegisterVaioGateFeedUpdateCompletedMessage();
void RegisterVaioGateItemLoadedMessage();
void RegisterChangeEditMessage();
void RegisterDrawFromEditMessage();
void RegisterDeleteChannelMessage();
void RegisterRenameChannelMessage();
void RegisterChannelClickMessage();