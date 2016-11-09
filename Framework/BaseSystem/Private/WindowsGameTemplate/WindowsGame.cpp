#include	"WindowsGame.h"

/*! =====================================================================================
@brief	�R���X�g���N�^
@param	�C���X�^���X�n���h��
====================================================================================== */
WindowsGame::WindowsGame(HINSTANCE _hInstance)
	:m_hInstance(_hInstance),
	m_hWnd(NULL){
}

/*! =====================================================================================
@brief	�f�X�g���N�^
@param	void
====================================================================================== */
WindowsGame::~WindowsGame()
{
}

/*! =====================================================================================
@brief	����������
@param	void
@return HRESULT
====================================================================================== */
HRESULT	WindowsGame::Initialize() {
	//�E�B���h�E
	if (FAILED(InitializeWindow())) {
		MessageBox(nullptr, TEXT("InitializeWindow() is fail"), TEXT("Error: WindowsGame.cpp"), MB_OK);
		return E_FAIL;
	}
	//�C���v�b�g
	if (FAILED(InitializeInput())) {
		MessageBox(nullptr, TEXT("InitializeInput() is fail"), TEXT("Error: WindowsGame.cpp"), MB_OK);
		return E_FAIL;
	}
	////�O���t�B�b�N
	if (FAILED(InitializeGraphics())) {
		MessageBox(nullptr, TEXT("InitializeGraphics() is fail"), TEXT("Error: WindowsGame.cpp"), MB_OK);
		return E_FAIL;
	}
	////�I�[�f�B�I
	//if (FAILED(InitializeAudio())) {
	//	MessageBox(nullptr, TEXT("�I�[�f�B�I���������s"), TEXT("Error: WindowsGame.cpp"), MB_OK);
	//	return E_FAIL;
	//}
	//�^�C�}�[
	if (FAILED(InitializeTimer())) {
		MessageBox(nullptr, TEXT("�^�C�}�[���������s"), TEXT("Error: WindowsGame.cpp"), MB_OK);
		return E_FAIL;
	}
	////�V�[���}�l�[�W���[
	//if (FAILED(InitializeSceneManager())) {
	//	MessageBox(nullptr, TEXT("�V�[�����������s"), TEXT("Error: WindowsGame.cpp"), MB_OK);
	//	return E_FAIL;
	//}

	return S_OK;
}

/*! =====================================================================================
@brief	�E�B���h�E�������E��������
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
@brief	�C���v�b�g������
@param	void
@return HRESULT
====================================================================================== */
HRESULT	WindowsGame::InitializeInput() {
	m_inputSystem.Initialize();
	return S_OK;
}

/*! =====================================================================================
@brief	�O���t�B�b�N�X������
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
@brief	�I�[�f�B�I������
@param	void
@return HRESULT
====================================================================================== */
//HRESULT	WindowsGame::InitializeAudio() {
//	Singleton<Audio>::GetInstance().Initialize();
//	return S_OK;
//}

/*! =====================================================================================
@brief	�^�C�}�[������
@param	void
@return HRESULT
====================================================================================== */
HRESULT	WindowsGame::InitializeTimer() {
	return	m_timerSystem.Initialize();
}

/*! =====================================================================================
@brief	�V�[���}�l�[�W���[������
@param	void
@return HRESULT
====================================================================================== */
//HRESULT	WindowsGame::InitializeSceneManager() {
//	m_SceneManager.Initialize();
//	return S_OK;
//}

/*! =====================================================================================
@brief	�����������A�ғ�
@param	void
@return INT	�I�����b�Z�[�W
====================================================================================== */
INT		WindowsGame::Run() {
	//������
	if (FAILED(Initialize())) {
		return 0;			//���������s�F�I��
	}
	//���b�Z�[�W���[�v
	return MessageLoop();	//�����������F�Q�[�����[�v�J�n
}

/*! =====================================================================================
@brief	���b�Z�[�W���[�v
@param	void
@return INT	�I�����b�Z�[�W
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
		MessageBox(NULL, _T("���b�Z�[�W���[�v�G���["), _T("�G���["), MB_OK);
	}
	return 0;
}

/*! =====================================================================================
@brief	�Q�[�����C��
@param	void
@return void
====================================================================================== */
void	WindowsGame::GameMain() {
	if (m_timerSystem.ControlFPS()) {
		UpdateInputSystem();	//���̓V�X�e���X�V
		//UpdateScene();	//�X�V����
		//Render();		//�`�揈��
	}
}

/*! =====================================================================================
@brief	���͏�ԍX�V
@param	void
@return void
====================================================================================== */
void WindowsGame::UpdateInputSystem() {
	m_inputSystem.UpdateAllInputDevice();
}

/*! =====================================================================================
@brief	�V�[���X�V
@param	void
@return void
====================================================================================== */
//void WindowsGame::UpdateScene() {
//	m_SceneManager.Update();
//}

/*! =====================================================================================
@brief	�`��X�V
@param	void
@return void
====================================================================================== */
//void WindowsGame::Render() {
//	if (SUCCEEDED(Renderer.BeginRender()))	//�`��J�n
//	{
//		m_SceneManager.RenderScene();
//		Renderer.EndRender();				//�`��I��
//	}
//	//�o�b�O�o�b�t�@�\��
//	Renderer.ShowBackbuffer();
//}