#pragma hdrstop
#include <tchar.h>
#include <windows.h>
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "Ask.h"// 通信補助DLL、Askに関するヘッダファイル

/* コンストラクタ */
Ask::Ask(){

	/* DLLをロードします */
	Dll = LoadLibrary("Ask.dll");
	if( Dll == NULL){
			_ASSERT(0);//エラーダイアログを表示
			Flag = FALSE;
			return ;
	}

	getVer  = (I2N)GetProcAddress( Dll , "getVer");
	createHandle  = (I2I)GetProcAddress( Dll , "createHandle");
	destroyHandle = (I2I)GetProcAddress( Dll , "destroyHandle");
	dispose = (I2N)GetProcAddress( Dll , "dispose");
	startServer = (I2ISSI)GetProcAddress( Dll , "startServer");
	startPeer = (I2ISSI)GetProcAddress( Dll , "startPeer");
	startConnect = (I2ISSI)GetProcAddress( Dll , "startConnect");
	disConnect = (I2I)GetProcAddress( Dll , "disConnect");
	sendText = (I2IS)GetProcAddress( Dll , "sendText");
	sendTextTo = (I2IIS)GetProcAddress( Dll , "sendTextTo");
	sendTextMe = (I2IS)GetProcAddress( Dll , "sendTextMe");
	sendBinary = (I2IIS)GetProcAddress( Dll , "sendBinary");
	sendBinaryTo = (I2SIII)GetProcAddress( Dll , "sendBinaryTo");
	getTextLine = (I2I)GetProcAddress( Dll , "getTextLine");
	getTextSize = (I2I)GetProcAddress( Dll , "getTextSize");
	getText = (I2IIS)GetProcAddress( Dll , "getText");
	getBinaryLine = (I2I)GetProcAddress( Dll , "getBinaryLine");
	getBinarySize = (I2I)GetProcAddress( Dll , "getBinarySize");
	getBinary = (I2IIS)GetProcAddress( Dll , "getBinary");
	clearTextBuffer = (I2I)GetProcAddress( Dll , "clearTextBuffer");
	clearBinaryBuffer = (I2I)GetProcAddress( Dll , "clearBinaryBuffer");
	createGroupe = (I2I)GetProcAddress( Dll , "createGroupe");
	destroyGroupe = (I2II)GetProcAddress( Dll , "destroyGroupe");
	joinGroupe = (I2III)GetProcAddress( Dll , "joinGroupe");
	leaveGroupe = (I2III)GetProcAddress( Dll , "leaveGroupe");
	getMyDpnid = (I2I)GetProcAddress( Dll , "getMyDpnid");
	getMyHostName = (I2IIS)GetProcAddress( Dll , "getMyHostName");
	getMyIpCount = (I2I)GetProcAddress( Dll , "getMyIpCount");
	getMyIp = (I2SIII)GetProcAddress( Dll , "getMyIp");
	getNodeCount = (I2I)GetProcAddress( Dll , "getNodeCount");
	getSessionName = (I2IIS)GetProcAddress( Dll , "getSessionName");
	setSessionName = (I2IS)GetProcAddress( Dll , "setSessionName");
	getDataSizeText = (I2I)GetProcAddress( Dll , "getDataSizeText");
	setDataSizeText = (I2II)GetProcAddress( Dll , "setDataSizeText");
	getDataSizeBinary = (I2I)GetProcAddress( Dll , "getDataSizeBinary");
	setDataSizeBinary = (I2II)GetProcAddress( Dll , "setDataSizeBinary");
	getDpnidIp = (I2SIII)GetProcAddress( Dll , "getDpnidIp");
	getDpnidPort = (I2II)GetProcAddress( Dll , "getDpnidPort");
	getTimeOutTime = (I2I)GetProcAddress( Dll , "getTimeOutTime");
	setTimeOutTime = (I2II)GetProcAddress( Dll , "setTimeOutTime");
	getRtryCount = (I2I)GetProcAddress( Dll , "getRtryCount");
	setRetryCount = (I2II)GetProcAddress( Dll , "setRetryCount ");
	getMaxNode = (I2I)GetProcAddress( Dll , "getMaxNode");
	setMaxNode = (I2II)GetProcAddress( Dll , "setMaxNode");
	kick = (I2II)GetProcAddress( Dll , "kick");






	return;
}

/* デストラクタ */
Ask::~Ask(){

	FreeLibrary(Dll);

	return;
}



//-------------------------------------------------
// バージョン取得
//-------------------------------------------------

//-------------------------------------------------
// Askバージョン取得
//-------------------------------------------------
int Ask::aGetVer(){
	if( Flag == FALSE) return -1;
	return getVer();
}

//-------------------------------------------------
// ハンドル取得・破棄
//-------------------------------------------------
int Ask::aCreateHandle(){
	if( Flag == FALSE) return -1;
	return createHandle(0);
}