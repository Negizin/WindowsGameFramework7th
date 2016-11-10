//!*******************************************************
//!	TsMatrix.h
//!
//!	çsóÒ
//!
//!	íòçÏå†	2016 Yuki Tsuneyama
//!	çÏê¨ì˙éû	16.01.14

#pragma once

#include <DirectXMath.h>

using namespace DirectX;



class Vector3;
class Vector4;
class Quaternion;

class Matrix : public XMFLOAT4X4 {
public:
	using oprator = XMFLOAT4X4;
	Matrix(XMFLOAT4X4& float4x4) :XMFLOAT4X4(float4x4) {};
	Matrix() { *this = Matrix::identity; };
	Matrix(XMMATRIX& matrix) { *this = matrix; }
	Matrix(Vector3& pos, Quaternion& rotate);
	Matrix(const Vector3& pos, const Quaternion& rotate, const Vector3& scale);

	Matrix& operator = (const XMMATRIX& matrix);
	Matrix  operator *  (const Matrix& matrix)const;
	Matrix& operator *= (const Matrix& matrix);

	XMMATRIX  ToXMMATRIX()const;
	Quaternion ToQuaternion()const;
	const Matrix& Transpose();
	Matrix& Inverse();

	Matrix Transposed()const;
	Matrix Inversed();

	Vector3 TransformCoord(const Vector3&);
	Vector3	TransformVector(const Vector3&);
	Vector3 TransformPoint(const Vector3&);
	Vector4 TransformVector(const Vector4&);

	bool operator == (const Matrix& matrix);
	bool operator != (const Matrix& matrix);

	static Matrix CreateTranslate(float x, float y, float z);
	static Matrix CreateTranslate(const Vector3& translate);
	static Matrix CreateRotate(const Quaternion& q);
	static Matrix CreateScale(float x, float y, float z);
	static Matrix CreateScale(const Vector3& scale);
	static Matrix CreateLookAt(const Vector3& eye, const Vector3& at, const Vector3& up);

	static const Matrix identity;

protected:
};