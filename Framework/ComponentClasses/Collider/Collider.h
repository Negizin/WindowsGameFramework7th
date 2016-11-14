/*! =====================================================================================
@file		Collider.h
@brief		�R���C�_�[�F�Փ˗p�R���|�[�l���g
@author		Takuya Kawakami
@date		2016.11.05	�V�K�쐬
====================================================================================== */
#pragma once
#include	"../Component.h"
#include	"../../GameProperty/ColliderID.h"
#include	"../../Utilities/Math/Vector/Vector.h"
#include	<list>

/*! =====================================================================================
@brief	�Փˏ�� �i�[�p �\����
====================================================================================== */
struct CollisionData {
	ColliderIdentifier	opponentID;	//�ՓˑΏۂ�ID
	Vector3	crossPoint;		//�Փ˓_
	Vector3 normalVector;	//�Փ˓_�ɂ�����@���x�N�g��
};



/*! =====================================================================================
@brief	�R���C�_�[�R���|�[�l���g�N���X
====================================================================================== */
class Collider :public	Component {
public:
	Collider(GameObject* const _pParent);
	virtual ~Collider();

	void	Initialize(const ColliderIdentifier& _collisionMask);

	const	ColliderIdentifier&	GetColliderID()const;
	const	CollisionData&	GetCollisionData()const;

private:
	ColliderIdentifier	m_colliderID;		//���g�̏Փ�ID
	ColliderIdentifier	m_collisionMask;	//�ՓˑΏ�ID�̃}�X�N
	CollisionData		m_collisionData;	//�Փˏ�� �i�[�p
};



/*! =====================================================================================
@brief	�R���C�_�[�R���|�[�l���g���X�g�̃��b�s���O�N���X�istd::list<Collider*>�j
====================================================================================== */
class ColliderList :public	std::list<Collider*> {
public:
	ColliderList();
	~ColliderList();

	void	Activate(bool _flg);
};



/*! =====================================================================================
@brief	�Փ˃^�C�v�̗�
====================================================================================== */
enum ColliderType {
	NOT_INITIALIZED,	//�񏉊������
	AABB,				//AxisAlignedBoundingBox�F�����s���E�{�b�N�X
	OBB,				//OrientedBoundingBox:�w�������E�{�b�N�X
	SPHERE,				//��
};