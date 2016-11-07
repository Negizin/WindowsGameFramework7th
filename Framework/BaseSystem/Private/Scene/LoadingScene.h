/*! =====================================================================================
@file		LoadingScene.h
@brief		ローディング画面用シーン
@author		Takuya Kawakami
@date		2016.11.07	新規作成
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
	BaseScene*	m_pNextScene;	//遷移先のシーンへのポインタ
};

