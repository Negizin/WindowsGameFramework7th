#include	"GameObject.h"
#include	"../ComponentClasses/Collider/Collider.h"
#include	"../ComponentClasses/Renderer/Renderer.h"

/*! =====================================================================================
@fn		コンストラクタ
@param	void
====================================================================================== */
GameObject::GameObject() :
	m_isActive(true), m_transform(this), m_pRenderer(nullptr) {
}

/*! =====================================================================================
@fn		デストラクタ
@param	void
====================================================================================== */
GameObject::~GameObject() {
	SafeDelete(m_pRenderer);
}

/*! =====================================================================================
@brief	衝突処理

「m_isActive が true」かつ「m_pCollider が nullptrでない」場合、衝突判定が行われる。
衝突判定により衝突が検知された場合、この関数が呼び出される。

@param	Collider*：衝突対象のコライダーコンポーネント
@return void
====================================================================================== */
void	GameObject::OnCollision(Collider*	_pOther) {
	//switch (_pOther->GetColliderID()) {
	//	default:	break;
	//}
}

/*! =====================================================================================
@brief	オブジェクトの更新処理を行うフラグの操作(セットされているコンポーネントも一括で操作)
@param	bool：true＝更新ON
====================================================================================== */
void GameObject::Activate(bool _flg) {
	m_isActive = _flg;
	m_colliderList.Activate(_flg);
	if (m_pRenderer != nullptr) { m_pRenderer->Activate(_flg); }
}

/*! =====================================================================================
@brief	オブジェクトの衝突判定を行うフラグの操作
@param	bool：true＝衝突ON
====================================================================================== */
void GameObject::ActivateCollider(bool _flg) {
	m_colliderList.Activate(_flg);
}

/*! =====================================================================================
@brief	オブジェクトの描画処理を行うフラグの操作
@param	bool：true＝描画ON
====================================================================================== */
void GameObject::ActivateRenderer(bool _flg) {
	if (m_pRenderer != nullptr) { m_pRenderer->Activate(_flg); }
}

/*! =====================================================================================
@brief	オブジェクトの更新処理を行うフラグの取得
@param	bool：true＝更新ON
====================================================================================== */
bool GameObject::GetActiveFlg() const {
	return m_isActive;
}

/*! =====================================================================================
@brief	オブジェクトのコライダーを取得
@param	bool：true＝更新ON
====================================================================================== */
ColliderList*	GameObject::GetComponentColliderList() {
	return &m_colliderList;
}

/*! =====================================================================================
@brief	オブジェクトのレンダラーを取得
@param	bool：true＝更新ON
====================================================================================== */
Renderer*	GameObject::GetComponentRenderer() const {
	return m_pRenderer;
}