#include	"SceneManager.h"
#include	"../../../BaseSystem/Public/Common/Common.h"
#include	"LoadScene.h"
#include	"../../../../DemoScene/DemoScene.h"
//#include	"TitleScene.h"
//#include	"..//Game/GameScene.h"
#include	<thread>

/*! =====================================================================================
@brief	コンストラクタ
@param	void
====================================================================================== */
SceneManager::SceneManager() {
}

/*! =====================================================================================
@brief	デストラクタ
@param	void
====================================================================================== */
SceneManager::~SceneManager() {
	SafeDelete(m_pNowScene);
	SafeDelete(m_pLoadScene);
}

/*! =====================================================================================
@brief	初期化処理
@param	void
@return void
====================================================================================== */
void	SceneManager::Initialize() {
	m_bNowLoading = true;
	//m_pLoadScene = new LoadScene(&m_bNowLoading);
	//m_pLoadScene->Initialize(new DemoScene());
	//m_pNextScene = m_pNowScene = m_pLoadScene;
	m_pNextScene = m_pNowScene = new DemoScene();
	m_pNowScene->Initialize();
}

/*! =====================================================================================
@brief	更新処理
@param	void
@return void
====================================================================================== */
void	SceneManager::Update() {

	if (m_pNowScene == nullptr) {
		return;
	}

	//シーンの更新処理
	//シーン遷移条件を満たされたとき、遷移先シーンのポインタが返される（遷移なしの場合はシーンのthisポインタが返される）
	m_pNextScene = m_pNowScene->Update();

	////シーン遷移あり
	//if (m_pNextScene != m_pNowScene) {
	//	//ローディングの完了によるシーン遷移の場合
	//	if (m_bNowLoading == true) {
	//		m_bNowLoading = false;		//ローディングOFF
	//		m_pNowScene = m_pNextScene;	//遷移先シーンをセット
	//	}
	//	//通常のゲームシーンから別のシーンへ遷移する場合
	//	else {
	//		m_bNowLoading = true;						//ローディングON
	//		m_pLoadScene->Initialize(m_pNextScene);		//遷移先シーンのポインタをローディングシーンに渡す
	//		m_pNextScene = m_pNowScene = m_pLoadScene;	//ローディング用シーンをセット
	//	}
	//}

}

/*! =====================================================================================
@brief	描画処理
@param	void
@return void
====================================================================================== */
void	SceneManager::SendDrawObject() {

	if (m_pNowScene == nullptr) {
		return;
	}

	m_pNowScene->UpdateRenderer();
}

/*! =====================================================================================
@brief	遷移先シーンの立ち上げ
@param	void
@return void
====================================================================================== */
void SceneManager::NextSceneLaunch() {

}
