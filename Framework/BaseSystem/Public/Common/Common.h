/*! =====================================================================================
@file		Common.h
@brief		ベースとなる各種共通プリプロセス、インクルード、ライブラリ、マクロ
@author		Takuya Kawakami
@date		2016.03.14	新規作成
====================================================================================== */
#pragma once

//	Windows.h インクルードファイル
#define WIN32_LEAN_AND_MEAN
#include	<Windows.h>

//	TCHAR対応(開発環境の設定に応じた文字列を使用する)
#include	"../../../BaseSystem/Private/Common/TCHARString.h"

//	デバッグモード時、メモリリーク検出強化
#include	"../../../BaseSystem/Private/Common/DebugNew.h"

//	SafeDelete系、フールプルーフ機能付き解放マクロ
#include	"../../../BaseSystem/Private/Common/SafeFunction.h"