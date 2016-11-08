#include	"LoadScene.h"
#include	<thread>

/*! =====================================================================================
@brief	コンストラクタ
@param	void
====================================================================================== */
LoadScene::LoadScene() {
	m_pNextScene = nullptr;
}

/*! =====================================================================================
@brief	コンストラクタ
@param	bool*	ロードスレッド管理用フラグへのポインタ
====================================================================================== */
LoadScene::LoadScene(bool * _pSyncFlg) {
	m_pNextScene = nullptr;
	m_pLoadingFlg = _pSyncFlg;
}

/*! =====================================================================================
@brief	デストラクタ
@param	void
====================================================================================== */
LoadScene::~LoadScene() {
}

/*! =====================================================================================
@brief	初期化処理
@param	void
@return void
====================================================================================== */
void LoadScene::Initialize() {
}

/*! =====================================================================================
@brief	初期化処理
@param	BaseScene*：遷移先シーン
@return void
====================================================================================== */
void LoadScene::Initialize(BaseScene * _pNextScene) {
	m_pNextScene = _pNextScene;
	std::thread	_loadThread(&LoadScene::Loading, this);	//別スレッドで遷移先のシーンを初期化する
	_loadThread.detach;
}

/*! =====================================================================================
@brief	更新処理
@param	void
@return void
====================================================================================== */
BaseScene * LoadScene::Update() {

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
			return m_pNextScene;	//遷移先シーンのポインタを返す
		}
	}
	else {
		return	this;	//シーン遷移なし
	}
}

/*! =====================================================================================
@brief	ローディング（別スレッドで実行されます）
@param	void
@return void
====================================================================================== */
void LoadScene::Loading() {
	m_pNextScene->Initialize();	//シーンの初期化開始
	*m_pLoadingFlg = false;		//初期化終了
}

/*! =====================================================================================
@brief	シーン遷移の条件判定
@param	void
@return bool	シーン遷移あり：true
====================================================================================== */
bool LoadScene::CheckSceneTransition() {

	//シーン開始・終了時のフェード中はシーン遷移を受け付けない
	//また、一度シーン遷移が決まったあとの遷移先変更も受け付けない
	if (m_pFadeSprite->GetFadingState() == true || m_nextSceneID != 0) {
		return false;
	}

	//ローディング完了判定
	if (*m_pLoadingFlg == true) {
		return false;	//ローディング中
	}
	else {
		m_nextSceneID = 1;
		return false;	//ローディング完了
	}
}