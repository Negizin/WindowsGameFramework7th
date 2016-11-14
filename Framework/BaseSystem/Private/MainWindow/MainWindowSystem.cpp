#include	"MainWindowSystem.h"
#include	"MainWindowNS.h"

//�t�@�C���ǂݍ��ݗp
#include <locale>
#include <iostream>
#include <fstream>
using namespace std;


namespace {
	tstring		g_sName;				//window��
	MainWindowSystem	*g_pWindow = nullptr;	//���b�Z�[�W�n���h���p

	//�E�B���h�E�v���V�[�W���p�R�[���o�b�N
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		return g_pWindow->MessageHandler(hWnd, uMsg, wParam, lParam);
	}
}

/*! =====================================================================================
@brief	�R���X�g���N�^
@param	void
====================================================================================== */
MainWindowSystem::MainWindowSystem() {
	SecureZeroMemory(this, sizeof(MainWindowSystem));
	g_pWindow = this;
	m_bInitialized = false;
}

/*! =====================================================================================
@brief	�f�X�g���N�^
@param	void
====================================================================================== */
MainWindowSystem::~MainWindowSystem() {
	g_pWindow = nullptr;
}

/*! =====================================================================================
@brief	�E�B���h�E�������E����
@param	�C���X�^���X�n���h��
@return HRESULT�A�E�B���h�E�����̐���or���s
====================================================================================== */
HRESULT	MainWindowSystem::Initialize(HINSTANCE hInstance) {
	//�t�@�C���ǂݍ���
	if (LoadCSV() == false) {
		return E_FAIL;
	}

	//�E�B���h�E�N���X�݌v
	WNDCLASSEX	wndclass;	//�E�B���h�E�̐������i�[����\����
	wndclass.cbSize = sizeof(WNDCLASSEX);		//�\���̂̃T�C�Y
	wndclass.style = CS_HREDRAW | CS_VREDRAW;	//�X�^�C���w��AH/V�EREDRAW�@��/�c�����ύX���ꂽ�ۂɃE�B���h�E�S�̂��ĕ`��
	wndclass.lpfnWndProc = WndProc;				//�E�B���h�E�v���V�[�W���i�̃A�h���X���w��j
	wndclass.cbClsExtra = 0;					//�⏕������
	wndclass.cbWndExtra = 0;					//�⏕������
	wndclass.hInstance = hInstance;				//���݂̃C���X�^���X�n���h��
	wndclass.hIcon = (HICON) LoadImage(
		NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);	//�A�C�R��
	wndclass.hCursor = (HCURSOR) LoadImage(
		NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);		//�}�E�X�J�[�\��
	wndclass.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);								//�w�i�F�h��Ԃ��u���V
	wndclass.lpszMenuName = NULL;				//���j���[��
	wndclass.lpszClassName = g_sName.c_str();	//TEXT("test");		//�E�B���h�E�N���X���O
	wndclass.hIconSm = (HICON) LoadImage(
		NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);	//�������A�C�R��

	if (RegisterClassEx(&wndclass) == NULL) {
		MessageBox(nullptr, _T("�E�B���h�E�o�^���s"), _T("Error:MainWindow.cpp"), MB_OK);
		return false;
	}

	//�E�B���h�E�\�����A�S��ʕ\����
	DWORD	style;
	if (false) {
		//style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
		style = WS_VISIBLE | WS_POPUP;
	}
	else {
		style = WS_OVERLAPPEDWINDOW;
	}

	//�E�B���h�E�쐬
	m_hWnd = CreateWindow(
		g_sName.c_str(),		//�E�B���h�E�N���X��
		g_sName.c_str(),		//�E�B���h�E��
		style,					//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,			//X���W
		CW_USEDEFAULT,			//Y���W
		MainWindowNS::WINDOW_WIDTH,	//�E�B���h�E����
		MainWindowNS::WINDOW_HEIGHT,	//�E�B���h�E�c��
		(HWND) NULL,			//�e�E�B���h�E�̃n���h��
		(HMENU) NULL,			//���j���[�n���h���A���͎q�E�B���h�EID
		hInstance,				//���݂̃C���X�^���X�n���h��
		(LPVOID) NULL);			//�E�B���h�E�쐬�f�[�^

	if (m_hWnd == NULL) {
		MessageBox(nullptr, _T("�E�B���h�E�������s"), _T("Error:MainWindow.cpp"), MB_OK);
		return E_FAIL;	//�E�B���h�E�������s
	}

	if (true) {
		//�t���X�N���[���ł͂Ȃ��ꍇ�A�E�B���h�E�ʒu����
		RECT _windowRect;
		RECT _clientRect;
		GetWindowRect(m_hWnd, &_windowRect);	//�E�B���h�E�̈�T�C�Y�擾
		GetClientRect(m_hWnd, &_clientRect);   //�N���C�A���g�̈�T�C�Y�擾
		SetWindowPos(
			m_hWnd,
			0,
			GetSystemMetrics(SM_CXSCREEN) / 2 - MainWindowNS::WINDOW_WIDTH / 2,
			GetSystemMetrics(SM_CYSCREEN) / 2 - MainWindowNS::WINDOW_HEIGHT / 2,
			(_windowRect.right - _windowRect.left) - (_clientRect.right - _clientRect.left) + MainWindowNS::WINDOW_WIDTH,
			(_windowRect.bottom - _windowRect.top) - (_clientRect.bottom - _clientRect.top) + MainWindowNS::WINDOW_HEIGHT,
			SWP_SHOWWINDOW);
	}

	//�E�B���h�E�\���E�X�V
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	//�f�o�C�X�R���e�L�X�g�擾
	m_hdc = GetDC(m_hWnd);

	//�}�E�X�|�C���^�\����\��
	ShowCursor(true);

	m_bInitialized = true;
	return	S_OK;
}

/*! =====================================================================================
@brief	���b�Z�[�W�n���h��
@param	HWND
@param	UINT
@param	WPARAM
@param	LPARAM
@return LRESULT
====================================================================================== */
LRESULT	MainWindowSystem::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (m_bInitialized) {     //�������ς݁˃��b�Z�[�W����
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
@brief	�A�v���P�[�V�����ݒ�ǂݍ���(CSV�t�@�C���ǂݍ���)
@param	void
@return bool�F������true�A���s��false
====================================================================================== */
bool	MainWindowSystem::LoadCSV() {
	ifstream ifs("assets\\csv\\ApplicationData\\windowData.csv", ios::in);
	if (ifs.fail()) {
		MessageBox(nullptr, _T("�t�@�C���ǂݍ��ݎ��s"), _T("Error:MainWindowSystem.cpp"), MB_OK);
		return false;
	}

	string	_token;
	int		_width = 0, _height = 0;
	//�`�� [�A�v���P�[�V������, ����������]
	getline(ifs, _token, ',');
	if (_token != "�A�v���P�[�V������") {
		MessageBox(nullptr, _T("�t�@�C�����s���Ȍ`���ɉ�₂���Ă���\��������܂��B"), _T("Error:windowData.txt"), MB_OK);
		return false;
	}
	getline(ifs, _token);

	//�v���W�F�N�g�̕����R�[�h�ɂ���ĕ���
#ifdef UNICODE
	setlocale(LC_CTYPE, "JPN");
	wstring	work = StringToWString(_token);
	g_sName = work;
#else
	g_sName = _token;
#endif

	//�`�� [��ʃT�C�Y��,xxxx]
	getline(ifs, _token, ',');
	if (_token != "��ʃT�C�Y��") {
		MessageBox(nullptr, _T("�t�@�C�����s���Ȍ`���ɉ�₂���Ă���\��������܂��B"), _T("Error:windowData.csv"), MB_OK);
		return false;
	}
	getline(ifs, _token);
	sscanf_s(_token.data(), "%d", &_width);

	//�`�� [��ʃT�C�Y����,xxxx]
	getline(ifs, _token, ',');
	if (_token != "��ʃT�C�Y��") {
		MessageBox(nullptr, _T("�t�@�C�����s���Ȍ`���ɉ�₂���Ă���\��������܂��B"), _T("Error:windowData.csv"), MB_OK);
		return false;
	}
	getline(ifs, _token);
	sscanf_s(_token.data(), "%d", &_height);

	//�f�[�^���L
	MainWindowNS::WINDOW_WIDTH = _width;
	MainWindowNS::WINDOW_HEIGHT = _height;

	ifs.close();
	return true;
}