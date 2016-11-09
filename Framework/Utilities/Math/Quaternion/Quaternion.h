//!*******************************************************
//!	TsQuaternion.h
//!
//!	クォータニオン
//!
//!	著作権	2016 Yuki Tsuneyama
//!	作成日時	16.01.14
#pragma once

#include <DirectXMath.h>
using namespace DirectX;

class Quaternion;
class Matrix;
class Vector3;
class Vector4;

//!*******************************************************
//!	[クラス] TsQuaternion
class Quaternion : public XMFLOAT4 {
public:
	using oprator = XMFLOAT4;
	Quaternion(float _x = 0, float _y = 0, float _z = 0, float _w = 1) :XMFLOAT4(_x, _y, _z, _w) {};
	Quaternion(XMFLOAT4 vector4) : XMFLOAT4(vector4.x, vector4.y, vector4.z, vector4.w) {};
	Quaternion(XMVECTOR vector) : XMFLOAT4(vector.m128_f32[0], vector.m128_f32[1], vector.m128_f32[2], vector.m128_f32[3]) {};
	XMVECTOR  ToXMVECTOR()const;
	Matrix	  ToMatrix()const;

	Quaternion& operator = (Matrix matrix);
	Quaternion  operator * (const Quaternion& quaternion)const;
	Quaternion& operator *=(const Quaternion& quaternion);

	static Quaternion AngleAxis(Vector3 axis, float angle);
	static const Quaternion identity;
protected:

};