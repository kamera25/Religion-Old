#pragma hdrstop
#include <tchar.h>
#include <windows.h>
#include <crtdbg.h>//�G���[�`�F�b�N���o����悤�ɂ��邽�߂̃w�b�_�t�@�C��
#include "Ask.h"// �ʐM�⏕DLL�AAsk�Ɋւ���w�b�_�t�@�C��

/* �R���X�g���N�^ */
Ask::Ask(){

	/* DLL�����[�h���܂� */
	Dll = LoadLibrary("Ask.dll");
	if(Dll == NULL){
			_ASSERT(0);//�G���[�_�C�A���O��\��
			return;
	}

	FARPROC proc = GetProcAddress(Dll, "startServer");
	if (proc == NULL)
	{
			_ASSERT(0);//�G���[�_�C�A���O��\��
			return;
	}

	return;
}

/* �f�X�g���N�^ */
Ask::~Ask(){

	FreeLibrary(Dll);

	return;
}