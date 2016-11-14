/*! =====================================================================================
@file		ObjectManager.h
@brief		オブジェクトマネージャー
@author		Takuya Kawakami
@date		2015.12.15	新規作成
====================================================================================== */
#pragma once
#include	<vector>
#include	<list>
class GameObject;

class ObjectManager {
public:
	ObjectManager();
	~ObjectManager();

	/*! =====================================================================================
	@brief	ゲームオブジェクト登録
	@param	GameObject*
	@return void
	====================================================================================== */
	void	RegisterObject(GameObject*	_pObject);

	/*! =====================================================================================
	@brief	指定したスレッド・オブジェクト配列にゲームオブジェクトを登録する
	@param	GameObject*	登録するゲームオブジェクト
	@param	unsigned	登録先のスレッド・オブジェクト配列のインデックス(0～3)
	@return void
	====================================================================================== */
	void	RegisterObject(GameObject*	_pObject, unsigned _threadIndex);

	void	Update();			//更新処理
	void	RendererUpdate();	//描画用キューに有効なｵﾌﾞｼﾞｪｸﾄをセット

private:
	//Data
	std::vector<GameObject*>	m_objectArray[4];

	//Method
	void	UpdateThread(unsigned	thread);

};