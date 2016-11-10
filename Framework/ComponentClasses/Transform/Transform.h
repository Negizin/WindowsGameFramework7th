/*! =====================================================================================
@file		Transform.h
@brief		オブジェクトの拡縮・回転・移動を管理するコンポーネント
@author		Takuya Kawakami
@date		2016.11.10　最終更新
====================================================================================== */
#pragma once
#include	"../Component.h"
#include	"../../Utilities/Math/Vector/Vector.h"
#include	"../../Utilities/Math/Quaternion/Quaternion.h"
#include	"../../Utilities/Math/Matrix/Matrix.h"
class GameObject;

class Transform :public Component {
public:
	Transform();
	Transform(const Vector3& _position, const Quaternion& _rotation, const Vector3& _scale = Vector3::one);
	Transform(const Matrix& _matrix);
	virtual ~Transform();	

	//
	void	SetPosition(const Vector3& _position);
	void	Translate(const Vector3& _vector);
	void	LookDirection(const Vector3& _direction);
	void	LookAt(const Vector3& _point);
	void	Resize(const Vector3& _scale);
	void	Scaling(const Vector3& _parameter);
	const	Vector3&	GetLocalScale()const;
	const	Quaternion&	GetLocalRotation()const;
	const	Vector3&	GetLocalPosition()const;
	//
	const	tstring&	GetName()const;
	const	GameObject*	GetGameObject()const;
	const	Transform*	GetParentTransform()const;
	//
	Matrix	ToWorldMatrix()const;
	Matrix	ToLocalMatrix()const;
	//
	void	SetGameObject(GameObject* _pObject);
	//
	Transform& operator= (const Matrix& m);
	Transform  operator* (const Matrix& m);
	Transform& operator*= (const Matrix& m);

private:
	//
	Vector3		m_scale;
	Quaternion	m_rotation;
	Vector3		m_position;
	
	//
	tstring		m_name;
	GameObject*	m_pGameObject;
	Transform*	m_pParent = nullptr;
	//TransForm*	m_pFirstChild = nullptr;
	//TransForm*	m_pSubling = nullptr;

};

