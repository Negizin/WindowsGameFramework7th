/*! =====================================================================================
@file		MainWindow.h
@brief		メインウィンドウ
@author		Takuya Kawakami
@date		2016.03.14
====================================================================================== */
#pragma once
#include	"../../../BaseSystem/Public/Common/Common.h"

class MainWindowSystem {
public:
	MainWindowSystem();
	~MainWindowSystem();
	//Method
	HRESULT		Initialize(HINSTANCE hInstance);
	LRESULT		MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//Getter
	HWND		GetHandleWindow()const { return m_hWnd; }
	HDC			GetHDC()const { return m_hdc; }

private:
	static	const	int	BUFFER_MAX = 64;
	//Data
	HWND		m_hWnd;
	HDC			m_hdc;
	bool		m_bInitialized;

	//Method
	bool	LoadCSV();

};

