/*! =====================================================================================
@file		TCHARString.h
@brief		TCHAR対応(開発環境の設定に応じた文字列)
@author		TakuyaKawakami
@date		2016.03.14	新規作成
====================================================================================== */
#pragma once
#include	<tchar.h>
#include	<string>
#include	<atlstr.h>

//TCHAR型の文字列型を命名
typedef	std::basic_string<TCHAR>	tstring;

//	数値⇒文字列変換マクロ	（UNICODE,マルチバイト別）
#if defined(UNICODE)
#define	to_tstring(value)	std::to_wstring(value)
#else	//マルチバイト
#define	to_tstring(value)	std::to_string(value)
#endif

/*! =====================================================================================
@brief	UNICODE文字列⇒マルチバイト文字列
@param	std::wstring	変換したいUNICODE文字列
@return std::string		変換後のマルチバイト文字列
====================================================================================== */
inline	std::string WStringToString(const std::wstring& _wstring) {
	CStringA	_work = _wstring.c_str();
	return std::string(_work);
};

/*! =====================================================================================
@brief	マルチバイト文字列⇒UNICODE文字列
@param	std::string		変換したいマルチバイト文字列
@return std::wstring	変換後のUNICODE文字列
====================================================================================== */
inline	std::wstring StringToWString(const std::string& _string) {
	CStringW	_work = _string.c_str();
	return std::wstring(_work);
};