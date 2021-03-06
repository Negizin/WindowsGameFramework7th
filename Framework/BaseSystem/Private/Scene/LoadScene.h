/*! =====================================================================================
@file		LoadingScene.h
@brief		ローディング画面用シーン
@author		Takuya Kawakami
@date		2016.11.07	新規作成
====================================================================================== */
#pragma once
#include	"../../../BaseSystem/Public/Scene/BaseScene.h"

class LoadScene :public	BaseScene{
public:
	LoadScene();
	LoadScene(bool* _pSyncFlg);
	~LoadScene();

	void	Initialize();
	void	Initialize(BaseScene* _pNextScene);
	BaseScene*	Update();

private:
	BaseScene*	m_pNextScene;	//遷移先のシーンへのポインタ
	bool*		m_pLoadingFlg;	//ローディングスレッド同期管理用フラグ
	
	bool	CheckSceneTransition();
	void	Loading();
};

