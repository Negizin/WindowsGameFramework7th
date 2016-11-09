/*! =====================================================================================
@file		NameObject.h
@brief		Class NameObject
@author
@date		2016.11.09	�ŏI�X�V
====================================================================================== */
#pragma once
#include "../File/File.h"

class NameObject {
public:

	/*! =====================================================================================
	@brief	���O�Z�b�g�A�n�b�V���l����
	@param	���O
	@return void
	====================================================================================== */
	void SetName(tstring str) {
		m_name = str;
		m_hashCode = UT::StringToHash(str);
	}

	/*! =====================================================================================
	@brief	���O�擾
	@param	void
	@return void
	====================================================================================== */
	tstring GetName()const { return m_name; }

	/*! =====================================================================================
	@brief	�n�b�V���l�擾
	@param	void
	@return void
	====================================================================================== */
	HASH GetHashCode()const { return m_hashCode; }

protected:
	tstring	m_name;
private:
	HASH	m_hashCode;
};