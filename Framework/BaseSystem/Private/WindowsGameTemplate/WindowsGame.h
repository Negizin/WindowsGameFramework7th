/*! =====================================================================================
@file		WindowsGame.h
@brief		Windowsゲームアプリケーション用テンプレートメソッド
@author		Takuya Kawakami
@date		2016.03.14
====================================================================================== */

#pragma once
#include	"../../../BaseSystem/Public/Common/Common.h"
#include	"../../../BaseSystem/Private/MainWindow/MainWindowSystem.h"
#include	"../../../BaseSystem/Private/DebugSystem/ConsoleWindow.h"
#include	"../../../BaseSystem/Private/Input/InputSystem.h"
#include	"../../../BaseSystem/Private/RenderSystem/RenderSystem.h"
#include	"../../../BaseSystem/Private/Timer/TimerSystem.h"

class WindowsGame {
public:
	WindowsGame(HINSTANCE _hInscance);
	~WindowsGame();
	//Method
	INT		Run();

private:
	//Data
	HINSTANCE			m_hInstance;
	HWND				m_hWnd;

	//System
	MainWindowSystem	m_mainWindowSystem;
	InputSystem			m_inputSystem;
	RenderSystem		m_renderSystem;
	TimerSystem			m_timerSystem;
	
	//SceneManager	m_sceneManager;

	//Method
	HRESULT	Initialize();
	HRESULT	InitializeWindow();
	HRESULT	InitializeInput();
	HRESULT	InitializeGraphics();
	HRESULT	InitializeTimer();

	//HRESULT	InitializeSceneManager();
	//HRESULT	InitializeAudio();
	INT		MessageLoop();
	void	GameMain();
	void	UpdateInputSystem();
	//void	UpdateScene();
	//void	Render();

};

