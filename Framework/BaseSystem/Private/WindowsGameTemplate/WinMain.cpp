/*! =====================================================================================
@file		WinMain.cpp
@brief		エントリーポイント。Windowsゲームアプリケーション用のテンプレート起動。
@author		Takuya Kawakami
@date		2016.06.14　
====================================================================================== */
#include	"WindowsGame.h"

INT	WINAPI	WinMain(HINSTANCE	hInstance, HINSTANCE hPreInstance, LPSTR lpStr, INT nCmdShow) {

#if defined(_DEBUG)	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	//デバッグ時:メモリリークチェック
#endif

	WindowsGame	_gameApplication(hInstance);
	return _gameApplication.Run();

}