/*! =====================================================================================
@file		DebugNew.h
@brief		デバッグモード時、メモリリーク検出・ファイルと行を特定してログを出力する
@author		Takuya Kawakami
@date		2016.11.02	新規作成
====================================================================================== */
#pragma once
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC	//mallocで確保されたヒープ領域を監視。（メモリリークの原因であるファイルと行を特定して出力）
#include <stdlib.h> 
#include <crtdbg.h>

#define DEBUG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) //newで確保されたヒープ領域を監視。（メモリリークの原因であるファイルと行を特定して出力）
#define new DEBUG_NEW

#endif // _DEBUG
