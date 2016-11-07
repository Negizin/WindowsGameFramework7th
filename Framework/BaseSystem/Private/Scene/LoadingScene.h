/*! =====================================================================================
@file		LoadingScene.h
@brief		���[�f�B���O��ʗp�V�[��
@author		Takuya Kawakami
@date		2016.11.07	�V�K�쐬
====================================================================================== */
#pragma once
#include	"../../../BaseSystem/Public/Scene/BaseScene.h"

class LoadingScene :public	BaseScene{
public:
	LoadingScene();
	~LoadingScene();

	void	Initialize();
	void	Initialize(BaseScene* _pNextScene);
	BaseScene*	Update();

private:
	BaseScene*	m_pNextScene;	//�J�ڐ�̃V�[���ւ̃|�C���^
};

