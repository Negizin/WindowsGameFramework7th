/*! =====================================================================================
@file		RenderSystemNS.h
@brief		描画に関するフレームワーク部とゲーム実装部(インターフェース)に共通のデータベースとしての名前空間
@author		Takuya Kawakami
@date		2016.11.11	新規作成
====================================================================================== */
#pragma once
#include	"DX11Device\DX11Device.h"

namespace {
	static	DX11Device*	g_pDevice = nullptr;
}