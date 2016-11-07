/*! =====================================================================================
@file		InputSystemNS.h
@brief		入力に関するフレームワーク部とゲーム実装部でのインターフェースに共通のデータを保持する名前空間
@author		Takuya Kawakami
@date		2016.11.03	新規作成
====================================================================================== */
#pragma once
#include	"KeyboardData.h"
#include	"XInputControllerData.h"

namespace {
	const	static	int		MAX_CONTROLLERS = 4;			//コントローラの最大数
	static	CONTROLER_STATE	g_controllers[MAX_CONTROLLERS];	//コントローラの入力データ
	static	KEYBOARD_STATE	g_keyboard;						//キーボードの入力データ

	const	static	short	DEADZONE_THUMB = (short) (32767.0f * 0.2f);	//スティックのデッドゾーン
	const	static	unsigned char	DEADZONE_TRIGGER = (unsigned char) (255.0f * 0.2f);	//トリガーデッドゾーン
}
