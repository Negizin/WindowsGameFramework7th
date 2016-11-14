/*! =====================================================================================
@file		BoundingBoxCollider.h
@brief		OrientedBoundingBox 指向性境界ボックス
@author		Takuya Kawakami
@date		2016.09.21	新規作成
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