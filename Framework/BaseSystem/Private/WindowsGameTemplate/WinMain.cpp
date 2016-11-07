/*! =====================================================================================
@file		WinMain.cpp
@brief		�G���g���[�|�C���g�BWindows�Q�[���A�v���P�[�V�����p�̃e���v���[�g�N���B
@author		Takuya Kawakami
@date		2016.06.14�@
====================================================================================== */
#include	"WindowsGame.h"

INT	WINAPI	WinMain(HINSTANCE	hInstance, HINSTANCE hPreInstance, LPSTR lpStr, INT nCmdShow) {

#if defined(_DEBUG)	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	//�f�o�b�O��:���������[�N�`�F�b�N
#endif

	WindowsGame	_gameApplication(hInstance);
	return _gameApplication.Run();

}