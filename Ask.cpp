#pragma hdrstop
#include <tchar.h>
#include <windows.h>
#include <crtdbg.h>//エラーチェックが出来るようにするためのヘッダファイル
#include "Ask.h"// 通信補助DLL、Askに関するヘッダファイル

/* コンストラクタ */
Ask::Ask(){

	/* DLLをロードします */
	Dll = LoadLibrary("Ask.dll");
	if(Dll == NULL){
			_ASSERT(0);//エラーダイアログを表示
			return;
	}

	FARPROC proc = GetProcAddress(Dll, "startServer");
	if (proc == NULL)
	{
			_ASSERT(0);//エラーダイアログを表示
			return;
	}

	return;
}

/* デストラクタ */
Ask::~Ask(){

	FreeLibrary(Dll);

	return;
}