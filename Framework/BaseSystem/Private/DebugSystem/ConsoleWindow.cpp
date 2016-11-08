#include	"ConsoleWindow.h"

//Debugモードのみで機能する
#ifdef _DEBUG
#include	<stdio.h>

ConsoleWindow	g_ConsoleWindow;

/*! =====================================================================================
@brief	コンストラクタ
@param	void
====================================================================================== */
ConsoleWindow::ConsoleWindow() {

	//コンソール作成
	AllocConsole();

	//標準入出力の割り当て
	FILE*	_fp;
	freopen_s(&_fp, "CONIN$", "r", stdin);		 // 標準入力の割り当て
	freopen_s(&_fp, "CONOUT$", "w", stdout);	 // 標準出力の割り当て

	HANDLE	_hStdIn = GetStdHandle(STD_INPUT_HANDLE);	 //標準入力ハンドルの取得
	HANDLE	_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);	 //標準入力ハンドルの取得

	//ウィンドウタイトル名セット
	SetConsoleTitleA("ConsoleWindow");
}

/*! =====================================================================================
@brief	デストラクタ
@param	void
====================================================================================== */
ConsoleWindow::~ConsoleWindow() {
	//コンソールウィンドウ解放
	FreeConsole();
}


#endif // _DEBUG