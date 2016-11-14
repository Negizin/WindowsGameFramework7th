#include	"BaseScene.h"
#include	"../../../GameObjectClasses/2D/FadeSprite.h"
#include	"../../Private/RenderSystem/SystemResource/DrawQueue.h"

/*! =====================================================================================
@brief	コンストラクタ	

	!! コンストラクタは継承先でも最低限の処理に抑えてください。
	!! ロードにコストを要するものは並列処理されるInitialize()に実装するようにしてください。

@param	void
====================================================================================== */
BaseScene::BaseScene() {
	m_pFadeSprite = new FadeSprite();
	m_objectManager.RegisterObject(m_pFadeSprite);
	m_nextSceneID = 0;

	m_pQueue = new DrawQueue();
}

/*! =====================================================================================
@brief	デストラクタ
@param	void
====================================================================================== */
BaseScene::~BaseScene() {
	SafeDelete(m_pQueue);
}

/*! =====================================================================================
@brief	更新処理
@param	void
@return void
====================================================================================== */
BaseScene * BaseScene::Update() {

	//全ｵﾌﾞｼﾞｪｸﾄの更新処理
	m_objectManager.Update();

	//シーン遷移判定
	if (CheckSceneTransition() == true) {
		m_pFadeSprite->StartFadeOut();	//フェードアウト開始
	}
	
	//シーン遷移中
	if (m_nextSceneID != 0) {
		//フェードアウトが完了
		if (m_pFadeSprite->GetFadingState() == false) {
			//遷移先シーンのポインタを返す
			switch (m_nextSceneID) {
				case	1:	return this;
				case	2:	return this;
				case	3:	return this;
				default: MessageBox(NULL, _T("Update() return value is invalid"), _T("Error:BaseScene.cpp"), MB_OK); return this;
			}
		}
	}
	else {
		//シーン遷移なし
		return	this;
	}
}


/*! =====================================================================================
@brief	描画前処理
@param	void
@return void
====================================================================================== */
void BaseScene::UpdateRenderer() {
	m_objectManager.RendererUpdate();
}

/*! =====================================================================================
@brief	シーン遷移の条件判定
@param	void
@return bool	シーン遷移あり：true
====================================================================================== */
bool BaseScene::CheckSceneTransition() {

	/* 実装例：継承先で条件式を実装してください */

	//シーン開始・終了時のフェード中はシーン遷移を受け付けない
	if (m_pFadeSprite->GetFadingState() == true || m_nextSceneID != 0) {
		return false;
	}

	//シーン遷移条件
	if (false) {
		m_nextSceneID = 1;
		return true;
	}
	else if(false){
		m_nextSceneID = 2;
		return true;
	}
	else {
		m_nextSceneID = 3;
		return true;
	}

	//シーン遷移なし
	return	false;
}
