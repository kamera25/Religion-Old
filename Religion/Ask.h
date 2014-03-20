#pragma once

class Ask{

private:
	HMODULE Dll;// DLLのHInstance
	bool Flag;

	typedef INT (WINAPI *I2N)   ( VOID   );
	typedef INT (WINAPI *I2I)   ( INT    );
	typedef INT (WINAPI *I2II)  ( INT    , INT    );
	typedef INT (WINAPI *I2III)  ( INT    , INT , INT );
	typedef INT (WINAPI *I2SIII)(  INT   , INT , INT , TCHAR* );
	typedef INT (WINAPI *I2IS)(  INT   , TCHAR* );
	typedef INT (WINAPI *I2IIS)(  INT   , INT , TCHAR* );
	typedef INT (WINAPI *I2ISSI)(  INT   , TCHAR* ,  TCHAR*, INT  );

	I2N getVer;
	I2I createHandle;
	I2I destroyHandle;
	I2N dispose;
	I2ISSI startServer;
	I2ISSI startPeer;
	I2ISSI startConnect;
	I2I disConnect;
	I2IS sendText;
	I2IIS sendTextTo;
	I2IS sendTextMe;
	I2IIS sendBinary;
	I2SIII sendBinaryTo;
	I2I getTextLine;
	I2I getTextSize;
	I2IIS getText;
	I2I getBinaryLine;
	I2I getBinarySize;
	I2IIS getBinary;
	I2I clearTextBuffer;
	I2I clearBinaryBuffer;
	I2I createGroupe;
	I2II destroyGroupe;
	I2III joinGroupe;
	I2III leaveGroupe;
	I2I getMyDpnid;
	I2IIS getMyHostName;
	I2I getMyIpCount;
	I2SIII getMyIp;
	I2I getNodeCount;
	I2IIS getSessionName;
	I2IS setSessionName;
	I2I getDataSizeText;
	I2II setDataSizeText;
	I2I getDataSizeBinary;
	I2II setDataSizeBinary;
	I2SIII getDpnidIp;
	I2II getDpnidPort;
	I2I getTimeOutTime;
	I2II setTimeOutTime;
	I2I getRtryCount;
	I2II setRetryCount;
	I2I getMaxNode;
	I2II setMaxNode;
	I2II kick;



public:

	
	Ask();// コンストラクタ
	~Ask();// デストラクタ

	/* 関数の宣言 */
	int aGetVer();
	int aCreateHandle();
	int aDestroyHandle( int handle );
	int aDispose();
	int aServer( int handle , TCHAR * sessionName , TCHAR * portNo , int msgMode );
	int aPeer( int handle , TCHAR * sessionName , TCHAR * portNo , int msgMode );
	int aConnect( int handle , TCHAR * ipNo , TCHAR * portNo , int msgMode );
	int aDisConnect( int handle );
	int aSendText( int handle , TCHAR * text );
	int aSendTextTo( int handle , int DPNID , TCHAR * text );
	int aSendTextMe( int handle , TCHAR * text );
	int aSendBinary( int handle , TCHAR * data );
	int aSendBinaryTo( int handle , int DPNID , TCHAR * data );
	int aGetTextLine( int handle );
	int aGetTextSize( int handle );
	int aGetText( int handle , int size , TCHAR * text );
	int aGetBinaryLine( int handle );
	int aGetBinarySize( int handle );
	int aGetBinary( int handle , int size , TCHAR * text );
	int aClearTextBuffer( int handle );
	int aClearBinaryBuffer( int handle );
	int aCreateGroupe( int handle );
	int aDestroyGroupe( int handle , int groupeDPNID );
	int aJoinGroupe( int handle , int groupeDPNID , int nodeDPNID );
	int aLeaveGroupe( int handle , int groupeDPNID , int nodeDPNID );
	int aGetMyDpnid( int handle );
	int aGetMyHostName( int size , TCHAR * text );
	int aGetMyIpCount( int handle );
	int aGetMyIp( int handle , int number , int size , TCHAR * text );
	int aGetNodeCount( int handle );
	int aGetSessionName( int handle , int size , TCHAR * text );
	int aSetSessionName( int handle , TCHAR * text );
	int aGetDataSizeText( int handle );
	int aSetDataSizeText( int handle , int size );
	int aGetDataSizeBinary( int handle );
	int aSetDataSizeBinary( int handle , int size );
	int aGetDpnidIp( int handle , int DPNID , int size , TCHAR * text );
	int aGetDpnidPort( int handle , int DPNID );
	int aGetTimeOutTime( int handle );
	int aSetTimeOutTime( int handle , int milisecond );
	int aGetRetryCount( int handle );
	int aSetRetryCount( int handle , int count );
	int aGetMaxNode( int handle );
	int aSetMaxNode( int handle , int count );
	int aGetSynthesisFlag( int handle );
	int aGetFlagOperating( int handle );
	int aGetFlagHost( int handle );
	int aGetFlagPeer( int handle );
	int aGetFlagConnect( int handle );
	int aGetFlagPostInMe( int handle );
	int aSetFlagPostInMe( int handle , int flag );
	int aGetFlagAutoPortOpen( int handle );
	int aSetFlagAutoPortOpen( int handle , int flag );
	int aKick( int handle , int DPNID );
	int aGetMsgID( TCHAR * string );

};