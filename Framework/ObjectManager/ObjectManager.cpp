#include	"ObjectManager.h"
#include	"../GameObjectClasses/GameObject.h"
#include	"../ComponentClasses/Collider/Collider.h"
#include	"../ComponentClasses/Renderer/Renderer.h"
#include <thread>

/*! =====================================================================================
@brief	コンストラクタ
@param	void
====================================================================================== */
ObjectManager::ObjectManager() {
}

/*! =====================================================================================
@brief	デストラクタ
@param	void
====================================================================================== */
ObjectManager::~ObjectManager() {
	for (size_t i = 0; i < 4; i++) {
		for (auto itr = m_objectArray[i].begin(); itr != m_objectArray[i].end(); itr++) {
			SafeDelete(*itr);
		}
	}
}

/*! =====================================================================================
@brief	ゲームオブジェクト登録
@param	GameObject*
@return void
====================================================================================== */
void	ObjectManager::RegisterObject(GameObject* setObject) {
	m_objectArray[0].push_back(setObject);
	if (setObject->GetComponentCollider() != nullptr) {
	
	}
}

/*! =====================================================================================
@brief	指定したスレッド・オブジェクト配列にゲームオブジェクトを登録する
@param	GameObject*	登録するゲームオブジェクト
@param	unsigned	登録先のスレッド・オブジェクト配列のインデックス(0～3)
@return void
====================================================================================== */
void ObjectManager::RegisterObject(GameObject * setObject, unsigned thread) {
	switch (thread) {
		case	0:	m_objectArray[0].push_back(setObject); return;
		case	1:	m_objectArray[1].push_back(setObject); return;
		case	2:	m_objectArray[2].push_back(setObject); return;
		case	3:	m_objectArray[3].push_back(setObject); return;
		default:	m_objectArray[0].push_back(setObject); return;
	}
	if (setObject->GetComponentCollider() != nullptr) {

	}
}

/*! =====================================================================================
@brief	各ｵﾌﾞｼﾞｪｸﾄ配列更新
@param	０～３のｵﾌﾞｼﾞｪｸﾄ配列のインデックス
@return void
====================================================================================== */
void ObjectManager::UpdateThread(unsigned thread) {
	for (unsigned int i = 0; i < m_objectArray[thread].size(); i++) {
		if (m_objectArray[thread][i]->GetActiveFlg()) {
			m_objectArray[thread][i]->Update();
		}
	}
}

/*! =====================================================================================
@brief	更新処理
@param	void
@return void
====================================================================================== */
void	ObjectManager::Update() {

	//4スレッドでオブジェクト配列毎に並列処理する
	std::thread	_second(&ObjectManager::UpdateThread, this, 1);
	std::thread	_third(&ObjectManager::UpdateThread, this, 2);
	std::thread	_fourth(&ObjectManager::UpdateThread, this, 3);
	UpdateThread(0);

	//各スレッドの終了待機
	_second.join();
	_third.join();
	_fourth.join();

	//衝突判定

}

/*! =====================================================================================
@brief	描画用キューに有効なオブジェクトをセット
@param	void
@return void
====================================================================================== */
void	ObjectManager::RendererUpdate() {
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < m_objectArray[i].size(); j++) {
			//「オブジェクトがアクティブ」かつ
			//「オブジェクトがRendererコンポーネントを持っている」かつ
			//「Rendererコンポーネントが有効」の場合、描画キューにセットする
			if (m_objectArray[i][j]->GetActiveFlg() != false &&
				m_objectArray[i][j]->GetComponentRenderer() != nullptr &&
				m_objectArray[i][j]->GetComponentRenderer()->GetActiveFlg() != false){

			}
		}
	}
}