	/*! =====================================================================================
@file		DemoScene.h
@brief		�f���V�[��
@author		Takuya Kawakami
@date		2016.11.11	�V�K�쐬
====================================================================================== */
#pragma once
#include	"../Framework/BaseSystem/Public/Scene/BaseScene.h"

class Camera;


class DemoScene :public BaseScene {
public:
	DemoScene();
	~DemoScene();

	void		Initialize();
	BaseScene*	Update();
	void		UpdateRenderer();

private:
	Camera*	m_pCamera;


};

