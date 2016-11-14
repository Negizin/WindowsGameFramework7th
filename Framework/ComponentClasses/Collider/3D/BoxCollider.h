/*! =====================================================================================
@file		BoundingBoxCollider.h
@brief		OrientedBoundingBox �w�������E�{�b�N�X
@author		Takuya Kawakami
@date		2016.09.21	�V�K�쐬
====================================================================================== */
#pragma once
#include	"../Collider.h"
#include	"../../../Utilities/Math/Vector/Vector.h"

struct BoxData {
	Vector3	centerPoint;
	Vector3	minPoint;
	Vector3	maxPoint;
	float	radius;
	Vector3	axisX, axisY, axisZ;
	Vector3	halfLength;
};


class BoxCollider :public Collider {
public:
	BoxCollider(GameObject* const _pParent);
	~BoxCollider();

private:


};