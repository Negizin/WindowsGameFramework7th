#include	"WindowsGame.h"

/*! =====================================================================================
@brief	コンストラクタ
@param	インスタンスハンドル
====================================================================================== */
WindowsGame::WindowsGame(HINSTANCE _hInstance)
	:m_hInstance(_hInstance),
	m_hWnd(NULL){
}

/*! =====================================================================================
@brief	デストラクタ
@param	void
====================================================================================== */
WindowsGame::~WindowsGame()
{
}

/*! =====================================================================================
@brief	初期化処理
@param	void
@return HRESULT
====================================================================================== */
HRESULT	WindowsGame::Initialize() {
	//ウィンドウ
	if (FAILED(InitializeWindow())) {
		MessageBox(nullptr, TEXT("InitializeWindow() is fail"), TEXT("Error: WindowsGame.cpp"), MB_OK);
		return E_FAIL;
	}
	//インプット
	if (FAILED(InitializeInput())) {
		MessageBox(nullptr, TEXT("InitializeInput() is fail"), TEXT("Error: WindowsGame.cpp"), MB_OK);
		return E_FAIL;
	}
	////グラフィック
	if (FAILED(InitializeGraphics())) {
		MessageBox(nullptr, TEXT("InitializeGraphics() is fail"), TEXT("Error: WindowsGame.cpp"), MB_OK);
		return E_FAIL;
	}
	////オーディオ
	//if (FAILED(InitializeAudio())) {
	//	MessageBox(nullptr, TEXT("オーディオ初期化失敗"), TEXT("Error: WindowsGame.cpp"), MB_OK);
	//	return E_FAIL;
	//}
	//タイマー
	if (FAILED(InitializeTimer())) {
		MessageBox(nullptr, TEXT("タイマー初期化失敗"), TEXT("Error: WindowsGame.cpp"), MB_OK);
		return E_FAIL;
	}
	////シーンマネージャー
	//if (FAILED(InitializeSceneManager())) {
	//	MessageBox(nullptr, TEXT("シーン初期化失敗"), TEXT("Error: WindowsGame.cpp"), MB_OK);
	//	return E_FAIL;
	//}

	return S_OK;
}

/*! =====================================================================================
@brief	ウィンドウ初期化・生成処理
@param	void
@return HRESULT
====================================================================================== */
HRESULT	WindowsGame::InitializeWindow() {
	if (FAILED(m_mainWindowSystem.Initialize(m_hInstance))) {
		return E_FAIL;
	}
	m_hWnd = m_mainWindowSystem.GetHandleWindow();
	return S_OK;
}

/*! =====================================================================================
@brief	インプット初期化
@param	void
@return HRESULT
====================================================================================== */
HRESULT	WindowsGame::InitializeInput() {
	m_inputSystem.Initialize();
	return S_OK;
}

/*! =====================================================================================
@brief	グラフィックス初期化
@param	void
@return HRESULT
====================================================================================== */
HRESULT	WindowsGame::InitializeGraphics() {
	if (false == m_renderSystem.Initialize(m_hWnd)) {
		return E_FAIL;
	}
	return S_OK;
}

/*! =====================================================================================
@brief	オーディオ初期化
@param	void
@return HRESULT
====================================================================================== */
//HRESULT	WindowsGame::InitializeAudio() {
//	Singleton<Audio>::GetInstance().Initialize();
//	return S_OK;
//}

/*! =====================================================================================
@brief	タイマー初期化
@param	void
@return HRESULT
====================================================================================== */
HRESULT	WindowsGame::InitializeTimer() {
	return	m_timerSystem.Initialize();
}

/*! =====================================================================================
@brief	シーンマネージャー初期化
@param	void
@return HRESULT
====================================================================================== */
//HRESULT	WindowsGame::InitializeSceneManager() {
//	m_SceneManager.Initialize();
//	return S_OK;
//}

/*! =====================================================================================
@brief	初期化完了、稼働
@param	void
@return INT	終了メッセージ
====================================================================================== */
INT		WindowsGame::Run() {
	//初期化
	if (FAILED(Initialize())) {
		return 0;			//初期化失敗：終了
	}
	//メッセージループ
	return MessageLoop();	//初期化成功：ゲームループ開始
}

/*! =====================================================================================
@brief	メッセージループ
@param	void
@return INT	終了メッセージ
====================================================================================== */
INT	WindowsGame::MessageLoop() {
	MSG msg;
	SecureZeroMemory(&msg, sizeof(MSG));
	try {
		int done = 0;
		while (msg.message != WM_QUIT) {
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			GameMain();
		}
		return	(INT)msg.wParam;
	}
	catch (...) {
		MessageBox(NULL, _T("メッセージループエラー"), _T("エラー"), MB_OK);
	}
	return 0;
}

/*! =====================================================================================
@brief	ゲームメイン
@param	void
@return void
====================================================================================== */
void	WindowsGame::GameMain() {
	if (m_timerSystem.ControlFPS()) {
		UpdateInputSystem();	//入力システム更新
		//UpdateScene();	//更新処理
		//Render();		//描画処理
	}
}

/*! =====================================================================================
@brief	入力状態更新
@param	void
@return void
====================================================================================== */
void WindowsGame::UpdateInputSystem() {
	m_inputSystem.UpdateAllInputDevice();
}

/*! =====================================================================================
@brief	シーン更新
@param	void
@return void
====================================================================================== */
//void WindowsGame::UpdateScene() {
//	m_SceneManager.Update();
//}

/*! =====================================================================================
@brief	描画更新
@param	void
@return void
====================================================================================== */
//void WindowsGame::Render() {
//	if (SUCCEEDED(Renderer.BeginRender()))	//描画開始
//	{
//		m_SceneManager.RenderScene();
//		Renderer.EndRender();				//描画終了
//	}
//	//バッグバッファ表示
//	Renderer.ShowBackbuffer();
//}