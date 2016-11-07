/*! =====================================================================================
@file		FadeSprite.h
@brief		2D�X�v���C�g�p�x�[�X�I�u�W�F�N�g
@author		Takuya Kawakami
@date		2016.11.07	�V�K�쐬
====================================================================================== */
#pragma once
#include	"Sprite2D.h"

class FadeSprite :public	Sprite2D {
public:
	FadeSprite();
	virtual ~FadeSprite();
	void	Update();

	/*! =====================================================================================
	@brief	�t�F�[�h�A�E�g�J�n
	====================================================================================== */
	void	StartFadeOut();

	/*! =====================================================================================
	@brief	�t�F�[�h��Ԏ擾
	@return bool:�t�F�[�h���Ȃ��true��Ԃ�
	====================================================================================== */
	bool	GetFadingState()const;

private:
	bool	m_bFirstFrame;	//�V�[���J�n�ŏ��̃t���[��
	bool	m_bFadeIN;		//�t�F�[�h�C���t���O
	bool	m_bFadeOUT;		//�t�F�[�h�A�E�g�t���O
	float	m_timer;		//�t�F�[�h�Ǘ��p�^�C�}�[
};
