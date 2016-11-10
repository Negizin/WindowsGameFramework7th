/*! =====================================================================================
@file		SceneManager.h
@brief		シーンマネージャー
@author		Takuya Kawakami
@date		2016.03.15	新規作成
====================================================================================== */
#pragma once
class BaseScene;
class LoadScene;

class SceneManager {
public:
	SceneManager();
	~SceneManager();

	void	Initialize();		//初期化処理
	void	Update();			//更新処理
	void	SendDrawObject();	//描画処理

private:
	BaseScene*	m_pNowScene;	//現在実行中のシーン
	BaseScene*	m_pNextScene;	//シーン遷移先受付用スタック


	bool		m_bNowLoading;	//シーン遷移中・ローディング中フラグ
	LoadScene*	m_pLoadScene;	//ローディングシーン

	void	NextSceneLaunch();	//遷移先シーンの立ち上げ
};


