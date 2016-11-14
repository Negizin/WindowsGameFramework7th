#include	"MainWindowSystem.h"
#include	"MainWindowNS.h"

//ファイル読み込み用
#include <locale>
#include <iostream>
#include <fstream>
using namespace std;


namespace {
	tstring		g_sName;				//window名
	MainWindowSystem	*g_pWindow = nullptr;	//メッセージハンドラ用

	//ウィンドウプロシージャ用コールバック
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		return g_pWindow->MessageHandler(hWnd, uMsg, wParam, lParam);
	}
}

/*! =====================================================================================
@brief	コンストラクタ
@param	void
====================================================================================== */
MainWindowSystem::MainWindowSystem() {
	SecureZeroMemory(this, sizeof(MainWindowSystem));
	g_pWindow = this;
	m_bInitialized = false;
}

/*! =====================================================================================
@brief	デストラクタ
@param	void
====================================================================================== */
MainWindowSystem::~MainWindowSystem() {
	g_pWindow = nullptr;
}

/*! =====================================================================================
@brief	ウィンドウ初期化・生成
@param	インスタンスハンドル
@return HRESULT、ウィンドウ生成の成功or失敗
====================================================================================== */
HRESULT	MainWindowSystem::Initialize(HINSTANCE hInstance) {
	//ファイル読み込み
	if (LoadCSV() == false) {
		return E_FAIL;
	}

	//ウィンドウクラス設計
	WNDCLASSEX	wndclass;	//ウィンドウの性質を格納する構造体
	wndclass.cbSize = sizeof(WNDCLASSEX);		//構造体のサイズ
	wndclass.style = CS_HREDRAW | CS_VREDRAW;	//スタイル指定、H/V・REDRAW　横/縦幅が変更された際にウィンドウ全体を再描画
	wndclass.lpfnWndProc = WndProc;				//ウィンドウプロシージャ（のアドレスを指定）
	wndclass.cbClsExtra = 0;					//補助メモリ
	wndclass.cbWndExtra = 0;					//補助メモリ
	wndclass.hInstance = hInstance;				//現在のインスタンスハンドル
	wndclass.hIcon = (HICON) LoadImage(
		NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);	//アイコン
	wndclass.hCursor = (HCURSOR) LoadImage(
		NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);		//マウスカーソル
	wndclass.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);								//背景色塗りつぶしブラシ
	wndclass.lpszMenuName = NULL;				//メニュー名
	wndclass.lpszClassName = g_sName.c_str();	//TEXT("test");		//ウィンドウクラス名前
	wndclass.hIconSm = (HICON) LoadImage(
		NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);	//小さいアイコン

	if (RegisterClassEx(&wndclass) == NULL) {
		MessageBox(nullptr, _T("ウィンドウ登録失敗"), _T("Error:MainWindow.cpp"), MB_OK);
		return false;
	}

	//ウィンドウ表示か、全画面表示か
	DWORD	style;
	if (false) {
		//style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
		style = WS_VISIBLE | WS_POPUP;
	}
	else {
		style = WS_OVERLAPPEDWINDOW;
	}

	//ウィンドウ作成
	m_hWnd = CreateWindow(
		g_sName.c_str(),		//ウィンドウクラス名
		g_sName.c_str(),		//ウィンドウ名
		style,					//ウィンドウスタイル
		CW_USEDEFAULT,			//X座標
		CW_USEDEFAULT,			//Y座標
		MainWindowNS::WINDOW_WIDTH,	//ウィンドウ横幅
		MainWindowNS::WINDOW_HEIGHT,	//ウィンドウ縦幅
		(HWND) NULL,			//親ウィンドウのハンドル
		(HMENU) NULL,			//メニューハンドル、又は子ウィンドウID
		hInstance,				//現在のインスタンスハンドル
		(LPVOID) NULL);			//ウィンドウ作成データ

	if (m_hWnd == NULL) {
		MessageBox(nullptr, _T("ウィンドウ生成失敗"), _T("Error:MainWindow.cpp"), MB_OK);
		return E_FAIL;	//ウィンドウ生成失敗
	}

	if (true) {
		//フルスクリーンではない場合、ウィンドウ位置調整
		RECT _windowRect;
		RECT _clientRect;
		GetWindowRect(m_hWnd, &_windowRect);	//ウィンドウ領域サイズ取得
		GetClientRect(m_hWnd, &_clientRect);   //クライアント領域サイズ取得
		SetWindowPos(
			m_hWnd,
			0,
			GetSystemMetrics(SM_CXSCREEN) / 2 - MainWindowNS::WINDOW_WIDTH / 2,
			GetSystemMetrics(SM_CYSCREEN) / 2 - MainWindowNS::WINDOW_HEIGHT / 2,
			(_windowRect.right - _windowRect.left) - (_clientRect.right - _clientRect.left) + MainWindowNS::WINDOW_WIDTH,
			(_windowRect.bottom - _windowRect.top) - (_clientRect.bottom - _clientRect.top) + MainWindowNS::WINDOW_HEIGHT,
			SWP_SHOWWINDOW);
	}

	//ウィンドウ表示・更新
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	//デバイスコンテキスト取得
	m_hdc = GetDC(m_hWnd);

	//マウスポインタ表示非表示
	ShowCursor(true);

	m_bInitialized = true;
	return	S_OK;
}

/*! =====================================================================================
@brief	メッセージハンドラ
@param	HWND
@param	UINT
@param	WPARAM
@param	LPARAM
@return LRESULT
====================================================================================== */
LRESULT	MainWindowSystem::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (m_bInitialized) {     //初期化済み⇒メッセージ処理
		switch (msg) {
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			case WM_KEYDOWN:
				//input->KeyDown(wParam);
				if (wParam == VK_ESCAPE) {
					DestroyWindow(hWnd);
				}
				return	0;
			//case WM_SYSKEYDOWN:
			//	input->KeyDown(wParam);
			//	return	0;
			//case WM_KEYUP:
			//	input->KeyUp(wParam);
			//	return	0;
			//case WM_SYSKEYUP:
			//	return 0;
			//case WM_CHAR:
			//	input->KeyIn(wParam);
			//	return 0;
			//	//case WM_PAINT:
			//	//	return	0;
			//case WM_CREATE:
			//	return 0;
			//case WM_MOUSEMOVE:
			//	Input.MouseIn(lParam);
			//	return 0;
			//case WM_INPUT:
			//	Input.MouseRawIn(lParam);
			//	return 0;
			//case WM_LBUTTONDOWN:
			//	Input.SetMouseLButton(true);
			//	Input.MouseIn(lParam);
			//	return 0;
			//case WM_LBUTTONUP:
			//	Input.SetMouseLButton(false);
			//	Input.MouseIn(lParam);
			//	return 0;
			//case WM_MBUTTONDOWN:
			//	Input.SetMouseMButton(true);
			//	Input.MouseIn(lParam);
			//	return 0;
			//case WM_MBUTTONUP:
			//	Input.SetMouseMButton(false);
			//	Input.MouseIn(lParam);
			//	return 0;
			//case WM_RBUTTONDOWN:
			//	Input.SetMouseRButton(true);
			//	Input.MouseIn(lParam);
			//	return 0;
			//case WM_RBUTTONUP:
			//	Input.SetMouseRButton(false);
			//	Input.MouseIn(lParam);
			//	return 0;
			//case WM_XBUTTONDOWN:
			//	Input.SetMouseXButton(wParam);
			//	Input.MouseIn(lParam);
			//	return	0;
			//case WM_XBUTTONUP:
			//	Input.SetMouseXButton(wParam);
			//	Input.MouseIn(lParam);
			//	return 0;
			//case WM_MOUSEWHEEL:
			//	Input.MouseWheelIn(wParam);
			//	return 0;
			//case WM_DEVICECHANGE:
			//	Input.CheckControllers();
			//	return 0;
			default:
				break;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/*! =====================================================================================
@brief	アプリケーション設定読み込み(CSVファイル読み込み)
@param	void
@return bool：成功＝true、失敗＝false
====================================================================================== */
bool	MainWindowSystem::LoadCSV() {
	ifstream ifs("assets\\csv\\ApplicationData\\windowData.csv", ios::in);
	if (ifs.fail()) {
		MessageBox(nullptr, _T("ファイル読み込み失敗"), _T("Error:MainWindowSystem.cpp"), MB_OK);
		return false;
	}

	string	_token;
	int		_width = 0, _height = 0;
	//形式 [アプリケーション名, あいうえお]
	getline(ifs, _token, ',');
	if (_token != "アプリケーション名") {
		MessageBox(nullptr, _T("ファイルが不正な形式に改竄されている可能性があります。"), _T("Error:windowData.txt"), MB_OK);
		return false;
	}
	getline(ifs, _token);

	//プロジェクトの文字コードによって分岐
#ifdef UNICODE
	setlocale(LC_CTYPE, "JPN");
	wstring	work = StringToWString(_token);
	g_sName = work;
#else
	g_sName = _token;
#endif

	//形式 [画面サイズ幅,xxxx]
	getline(ifs, _token, ',');
	if (_token != "画面サイズ幅") {
		MessageBox(nullptr, _T("ファイルが不正な形式に改竄されている可能性があります。"), _T("Error:windowData.csv"), MB_OK);
		return false;
	}
	getline(ifs, _token);
	sscanf_s(_token.data(), "%d", &_width);

	//形式 [画面サイズ高さ,xxxx]
	getline(ifs, _token, ',');
	if (_token != "画面サイズ高") {
		MessageBox(nullptr, _T("ファイルが不正な形式に改竄されている可能性があります。"), _T("Error:windowData.csv"), MB_OK);
		return false;
	}
	getline(ifs, _token);
	sscanf_s(_token.data(), "%d", &_height);

	//データ共有
	MainWindowNS::WINDOW_WIDTH = _width;
	MainWindowNS::WINDOW_HEIGHT = _height;

	ifs.close();
	return true;
}