/*! =====================================================================================
@file		BaseScene.h
@brief		�x�[�X�V�[���N���X
@author		Takuya Kawakami
@date		2015.12.15	�V�K�쐬
====================================================================================== */

//===========================================================================================================
//	�E�x�[�X�V�[���N���X
//	���̃N���X����h�����āA�^�C�g���V�[���E�Q�[���V�[���E���U���g�V�[���Ȃǂ��������܂��B
//	�e�V�[���̓I�u�W�F�N�g�}�l�[�W���[�������Ă���A�}�l�[�W���̓V�[�����̑S�I�u�W�F�N�g���Ǘ����܂��B
//	�X�V�������A�V�[���J�ڂ��K�v�ȏꍇ�͑J�ڐ�̃V�[���ւ̃|�C���^��Ԃ��܂��B�J�ڂ��Ȃ��ꍇ�́Athis�|�C���^��Ԃ��܂��B
//===========================================================================================================

#pragma once
#include	"../../../ObjectManager/ObjectManager.h"
#include	"../../../GameObjectClasses/2D/FadeSprite.h"

class BaseScene {
public:
	BaseScene();
	virtual	~BaseScene();

	virtual	void		Initialize() = 0;
	virtual	BaseScene*	Update();
	virtual	void		UpdateRenderer();

protected:
	ObjectManager	m_objectManager;	//�I�u�W�F�N�g�Ǘ��N���X

	FadeSprite*		m_pFadeSprite;		//�t�F�[�h�Ɏg�p����X�v���C�g�I�u�W�F�N�g
	int				m_nextSceneID;		//�V�[���J��ID
	virtual	bool	CheckSceneTransition();	
};

