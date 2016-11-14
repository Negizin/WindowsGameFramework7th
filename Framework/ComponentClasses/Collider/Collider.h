/*! =====================================================================================
@file		Collider.h
@brief		コライダー：衝突用コンポーネント
@author		Takuya Kawakami
@date		2016.11.05	新規作成
====================================================================================== */
#pragma once
#include	"../Component.h"
#include	"../../GameProperty/ColliderID.h"
#include	"../../Utilities/Math/Vector/Vector.h"
#include	<list>

/*! =====================================================================================
@brief	衝突情報 格納用 構造体
====================================================================================== */
struct CollisionData {
	ColliderIdentifier	opponentID;	//衝突対象のID
	Vector3	crossPoint;		//衝突点
	Vector3 normalVector;	//衝突点における法線ベクトル
};



/*! =====================================================================================
@brief	コライダーコンポーネントクラス
====================================================================================== */
class Collider :public	Component {
public:
	Collider(GameObject* const _pParent);
	virtual ~Collider();

	void	Initialize(const ColliderIdentifier& _collisionMask);

	const	ColliderIdentifier&	GetColliderID()const;
	const	CollisionData&	GetCollisionData()const;

private:
	ColliderIdentifier	m_colliderID;		//自身の衝突ID
	ColliderIdentifier	m_collisionMask;	//衝突対象IDのマスク
	CollisionData		m_collisionData;	//衝突情報 格納用
};



/*! =====================================================================================
@brief	コライダーコンポーネントリストのラッピングクラス（std::list<Collider*>）
====================================================================================== */
class ColliderList :public	std::list<Collider*> {
public:
	ColliderList();
	~ColliderList();

	void	Activate(bool _flg);
};



/*! =====================================================================================
@brief	衝突タイプの列挙
====================================================================================== */
enum ColliderType {
	NOT_INITIALIZED,	//非初期化状態
	AABB,				//AxisAlignedBoundingBox：軸平行境界ボックス
	OBB,				//OrientedBoundingBox:指向性境界ボックス
	SPHERE,				//球
};