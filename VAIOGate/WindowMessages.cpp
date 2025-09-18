#include "WindowMessages.h"

void RegisterVaioGateCloseMessage() {
	g_vaioGateCloseMsg = RegisterWindowMessageW(L"VAIO_GATE_CLOSE_{748EA73B-5C77-4a74-A943-6AA90464ABDC}");
}

void RegisterVaioGateLaunchKbMessage() {
	g_vaioGateLaunchKbMsg = RegisterWindowMessageW(L"VAIO_GATE_LAUNCHKB_{24324303-77C2-41eb-BDBC-B251608C76DD}");
}

void RegisterVaioGateLaunchRemoteControlMessage() {
	g_vaioGateLaunchRemoteControlMsg = RegisterWindowMessageW(L"VAIO_GATE_LAUNCHREMOCON_{1EBEF9E1-C800-4190-99CD-0A9D2260CC75}");
}

void RegisterVaioGateLaunchSecondMessage() {
	g_vaioGateLaunchSecondMsg = RegisterWindowMessageW(L"VAIO_GATE_LAUNCHSECOND_{1EBEF9E1-C800-4190-99CD-0A9D2260CC77}");
}

void RegisterVaioGateOpenHelpFileMessage() {
	g_vaioGateOpenHelpFileMsg = RegisterWindowMessageW(L"VAIO_GATE_OPEN_HELP_FILE_{6AAFC21A-9337-4bd6-889C-82D676A5C25E}");
}

void RegisterVaioGatePressEscMessage() {
	g_vaioGatePressEscMsg = RegisterWindowMessageW(L"VAIO_GATE_PRESSESC_{BE646215-39FA-44e5-9EEA-BADFD9E65465}");
}

void RegisterVaioGateAddFeedMessage() {
	g_vaioGateAddFeedMsg = RegisterWindowMessageW(L"VG_MESSAGE_ADD_FEED");
}

void RegisterVaioGateFeedUpdateCompletedMessage() {
	g_vaioGateFeedUpdateCompletedMsg = RegisterWindowMessageW(L"VG_MESSAGE_FEED_UPDATE_COMPLETED");
}

void RegisterVaioGateItemLoadedMessage() {
	g_vaioGateItemLoadedMsg = RegisterWindowMessageW(L"VG_MESSAGE_ITEM_LOADED");
}

void RegisterChangeEditMessage() {
	g_changeEditMsg = RegisterWindowMessageW(L"ChangeEdit");
}

void RegisterDrawFromEditMessage() {
	g_drawFromEditMsg = RegisterWindowMessageW(L"DrawFromEdit");
}

void RegisterDeleteChannelMessage() {
	g_deleteChannelMsg = RegisterWindowMessageW(L"DeleteChannel");
}

void RegisterRenameChannelMessage() {
	g_renameChannelMsg = RegisterWindowMessageW(L"RenameChannel");
}

void RegisterChannelClickMessage() {
	g_channelClickMsg = RegisterWindowMessageW(L"ChannelClick");
}