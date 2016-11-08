/*! =====================================================================================
@file		BaseScene.h
@brief		ベースシーンクラス
@author		Takuya Kawakami
@date		2015.12.15	新規作成
====================================================================================== */

//===========================================================================================================
//	・ベースシーンクラス
//	このクラスから派生して、タイトルシーン・ゲームシーン・リザルトシーンなどを実装します。
//	各シーンはオブジェクトマネージャーを持っており、マネージャはシーン内の全オブジェクトを管理します。
//	更新処理中、シーン遷移が必要な場合は遷移先のシーンへのポインタを返します。遷移がない場合は、thisポインタを返します。
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
	ObjectManager	m_objectManager;	//オブジェクト管理クラス

	FadeSprite*		m_pFadeSprite;		//フェードに使用するスプライトオブジェクト
	int				m_nextSceneID;		//シーン遷移ID
	virtual	bool	CheckSceneTransition();	
};

