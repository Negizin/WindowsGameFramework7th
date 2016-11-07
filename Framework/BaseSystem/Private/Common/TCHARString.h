/*! =====================================================================================
@file		TCHARString.h
@brief		TCHAR�Ή�(�J�����̐ݒ�ɉ�����������)
@author		TakuyaKawakami
@date		2016.03.14	�V�K�쐬
====================================================================================== */
#pragma once
#include	<tchar.h>
#include	<string>
#include	<atlstr.h>

//TCHAR�^�̕�����^�𖽖�
typedef	std::basic_string<TCHAR>	tstring;

//	���l�˕�����ϊ��}�N��	�iUNICODE,�}���`�o�C�g�ʁj
#if defined(UNICODE)
#define	to_tstring(value)	std::to_wstring(value)
#else	//�}���`�o�C�g
#define	to_tstring(value)	std::to_string(value)
#endif

/*! =====================================================================================
@brief	UNICODE������˃}���`�o�C�g������
@param	std::wstring	�ϊ�������UNICODE������
@return std::string		�ϊ���̃}���`�o�C�g������
====================================================================================== */
inline	std::string WStringToString(const std::wstring& _wstring) {
	CStringA	_work = _wstring.c_str();
	return std::string(_work);
};

/*! =====================================================================================
@brief	�}���`�o�C�g�������UNICODE������
@param	std::string		�ϊ��������}���`�o�C�g������
@return std::wstring	�ϊ����UNICODE������
====================================================================================== */
inline	std::wstring StringToWString(const std::string& _string) {
	CStringW	_work = _string.c_str();
	return std::wstring(_work);
};