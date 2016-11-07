/*! =====================================================================================
@file		Input.h
@brief		入力機能管理クラス
@author		Takuya Kawakami
@date		2016.11.03	新規作成
====================================================================================== */
#pragma once
#include	"KeyboardData.h"
#include	"XInputControllerData.h"

//入力の状態管理
class InputSystem {
public:
	InputSystem();
	~InputSystem();

	/*! =====================================================================================
	@brief	初期化処理
	@param	void
	@return void
	====================================================================================== */
	void	Initialize();

	/*! =====================================================================================
	@brief	全入力デバイスの状態更新
	@param	void
	@return void
	====================================================================================== */
	void	UpdateAllInputDevice();

private:
	void	UpdateKeyboard();
	void	UpdateController();
};