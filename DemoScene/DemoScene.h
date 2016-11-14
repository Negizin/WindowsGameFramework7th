	/*! =====================================================================================
@file		DemoScene.h
@brief		デモシーン
@author		Takuya Kawakami
@date		2016.11.11	新規作成
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

private:
	Camera*	m_pCamera;


};

