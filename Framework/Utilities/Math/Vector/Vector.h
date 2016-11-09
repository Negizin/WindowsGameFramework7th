#pragma once

#include <DirectXMath.h>
using namespace DirectX;

class Vector2;
class Vector3;
class Vector4;
class Quaternion;
class Matrix;

//!*******************************************************
//!	[クラス] Vector2
class Vector2 : public XMFLOAT2 {
public:

	using oprator = XMFLOAT2;

	Vector2(float _x = 0, float _y = 0) :XMFLOAT2(_x, _y) {};
	Vector2(XMFLOAT2 vector2) :XMFLOAT2(vector2) {};
	Vector2(XMFLOAT3 vector3) :XMFLOAT2(vector3.x, vector3.y) {};
	Vector2(XMFLOAT4 vector4) :XMFLOAT2(vector4.x, vector4.y) {};
	Vector2(XMVECTOR vector) :XMFLOAT2(vector.m128_f32[0], vector.m128_f32[1]) {};

	Vector2& operator= (const XMVECTOR& Float2);

	Vector2  operator+ (const XMFLOAT2& Float2)const;
	Vector2  operator- (const XMFLOAT2& Float2)const;
	Vector2  operator* (float Float)const;
	Vector2  operator/ (float Float)const;

	Vector2& operator+= (const XMFLOAT2& Float2);
	Vector2& operator-= (const XMFLOAT2& Float2);
	Vector2& operator*= (float Float);
	Vector2& operator/= (float Float);

	bool operator==(const Vector2& value)const;
	bool operator!=(const Vector2& value)const;
	bool operator>=(const Vector2& value)const;
	bool operator<=(const Vector2& value)const;
	bool operator>(const Vector2& value)const;
	bool operator<(const Vector2& value)const;


	XMVECTOR  ToXMVECTOR()const;
	float	  Length()const;
	Vector2& Normalize();
	Vector2  Normalized()const;


	static float Dot(Vector2 v0,
		Vector2 v1);

	static Vector2 Closs(Vector2 v0,
		Vector2 v1);

	static const Vector2 zero;
	static const Vector2 one;
	static const Vector2 up;
	static const Vector2 down;
	static const Vector2 left;
	static const Vector2 right;

protected:

};


//!*******************************************************
//!	[クラス] Vector3
class Vector3 : public XMFLOAT3 {
public:

	using oprator = XMFLOAT3;

	Vector3(float _x = 0, float _y = 0, float _z = 0) :XMFLOAT3(_x, _y, _z) {};
	Vector3(XMFLOAT2 vector2) :XMFLOAT3(vector2.x, vector2.y, 0) {};
	Vector3(XMFLOAT3 vector3) :XMFLOAT3(vector3.x, vector3.y, vector3.z) {};
	Vector3(XMFLOAT4 vector4) :XMFLOAT3(vector4.x, vector4.y, vector4.z) {};
	Vector3(XMVECTOR vector) :XMFLOAT3(vector.m128_f32[0], vector.m128_f32[1], vector.m128_f32[2]) {};

	Vector3& operator= (const XMVECTOR& Float3);

	Vector3  operator+ (const XMFLOAT3& Float3)const;
	Vector3  operator- (const XMFLOAT3& Float3)const;
	Vector3  operator* (float Float)const;
	Vector3  operator/ (float Float)const;

	Vector3& operator+= (const XMFLOAT3& Float3);
	Vector3& operator-= (const XMFLOAT3& Float3);
	Vector3& operator*= (float Float);
	Vector3& operator/= (float Float);

	Vector3  operator*(const  Matrix& mat)const;
	Vector3& operator*=(const  Matrix& mat);

	bool operator==(const Vector3& value)const;
	bool operator!=(const Vector3& value)const;
	bool operator>=(const Vector3& value)const;
	bool operator<=(const Vector3& value)const;
	bool operator>(const Vector3& value)const;
	bool operator<(const Vector3& value)const;


	Vector3& TransformCood(const  Matrix& mat);
	XMVECTOR  ToXMVECTOR()const;
	float	  Length()const;
	Vector3& Normalize();
	Vector3  Normalized()const;


	static float Dot(Vector3 v0,
		Vector3 v1);

	static Vector3 Cross(Vector3 v0,
		Vector3 v1);

	static float CrossingAngle(Vector3 v0, Vector3 v1);

	static const Vector3 zero;
	static const Vector3 one;
	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 left;
	static const Vector3 right;
	static const Vector3 front;
	static const Vector3 back;

protected:

};


//!*******************************************************
//!	[クラス] Vector4
class Vector4 : public XMFLOAT4 {
public:

	using oprator = XMFLOAT4;

	Vector4(float _x = 0, float _y = 0, float _z = 0, float _w = 0) :XMFLOAT4(_x, _y, _z, _w) {};
	Vector4(XMFLOAT2 vector2) :XMFLOAT4(vector2.x, vector2.y, 0, 0) {};
	Vector4(XMFLOAT3 vector3) :XMFLOAT4(vector3.x, vector3.y, vector3.z, 0) {};
	Vector4(XMFLOAT4 vector4) :XMFLOAT4(vector4.x, vector4.y, vector4.z, vector4.w) {};
	Vector4(XMVECTOR vector) :XMFLOAT4(vector.m128_f32[0], vector.m128_f32[1], vector.m128_f32[2], vector.m128_f32[3]) {};

	Vector4& operator= (const XMVECTOR& Float4);
	Vector4& operator= (const XMFLOAT3& Float3);

	Vector4  operator+ (const XMFLOAT4& Float4)const;
	Vector4  operator- (const XMFLOAT4& Float4)const;
	Vector4  operator* (float Float)const;
	Vector4  operator/ (float Float)const;

	Vector4& operator+= (const XMFLOAT4& Float4);
	Vector4& operator-= (const XMFLOAT4& Float4);
	Vector4& operator*= (float Float);
	Vector4& operator/= (float Float);

	Vector4  operator * (const  Matrix& mat);
	Vector4& operator *=(const  Matrix& mat);

	bool operator==(const Vector4& value)const;
	bool operator!=(const Vector4& value)const;
	bool operator>=(const Vector4& value)const;
	bool operator<=(const Vector4& value)const;
	bool operator>(const Vector4& value)const;
	bool operator<(const Vector4& value)const;

	XMVECTOR  ToXMVECTOR()const;
	float	  Length()const;
	Vector4& Normalize();
	Vector4  Normalized()const;


	static float Dot(Vector4 v0,
		Vector4 v1);

	static Vector4 Closs(Vector4 v0,
		Vector4 v1);

	static const Vector4 zero;
	static const Vector4 one;
	static const Vector4 up;
	static const Vector4 down;
	static const Vector4 left;
	static const Vector4 right;
	static const Vector4 front;
	static const Vector4 back;

protected:

};