//!*******************************************************
//!	TsBinaryFile.h
//!
//!	Binary Loader.
//!

#pragma once
#include	"../NameObject/NameObject.h"

class Binary : public NameObject
{
public:

	//! Constructor
	Binary();
	Binary(const Binary& bin);
	Binary(tstring filename);

	//! Destructor
	virtual~Binary();

	//=================================================
	// Load
	// �o�C�i���t�@�C����ǂݍ���
	// @pram filename	�ǂݍ��ݑΏۂ̃o�C�i���̃t�@�C���p�X
	// @return true is Success
	bool Load(tstring filename);

	//=================================================
	// UnLoad
	// �o�C�i���t�@�C�����J������B���̃��\�b�h�͖����I�ɌĂ�
	//�@�K�v�͂Ȃ��B
	// @pram filename	�ǂݍ��ݑΏۂ̃o�C�i���̃t�@�C���p�X
	// @return true is Success
	void UnLoad();

	//=================================================
	// GetBinary
	// �o�C�i���\�[�X�f�[�^���擾����
	// @return Binary Pointer
	unsigned char* GetBinary()const;

	//=================================================
	// GetBinary
	// �o�C�i���\�[�X�f�[�^���擾����
	// @return Binary Pointer
	int	GetSize()const;

	//=================================================
	// �R�s�[���s���ۂ͐V���ȃ������̊m�ۂ��s����B
	Binary operator = (const Binary& bin);
protected:
	unsigned char * m_bin;
	int    m_size;
};