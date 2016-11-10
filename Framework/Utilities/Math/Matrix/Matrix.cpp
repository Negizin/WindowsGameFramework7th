#include "Matrix.h"
#include "../Vector/Vector.h"
#include "../Quaternion/Quaternion.h"
#include <memory.h>

const Matrix Matrix::identity = XMFLOAT4X4(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1);

//! 位置と回転から行列を生成するコンストラクタ
Matrix::Matrix(Vector3& p, Quaternion& q) {
	*this = CreateRotate(q) * CreateTranslate(p);
}

//! 位置と回転と拡縮から行列を生成するコンストラクタ
Matrix::Matrix(const Vector3& _position, const Quaternion& _quaternion, const Vector3& _scale) {
	*this = CreateScale(_scale) * CreateRotate(q) * CreateTranslate(_position);
}

//! XNA行列からの変換用
Matrix&  Matrix::operator =(const XMMATRIX& i) {
	memcpy(m, i.r, sizeof(float) * 16);
	return *this;
}

//! 行列の掛け算計算はXNAVECTORのsimdを利用する
Matrix  Matrix::operator *(const Matrix& matrix)const {
	return Matrix(ToXMMATRIX() * matrix.ToXMMATRIX());
}

Matrix& Matrix::operator*= (const Matrix& matrix) {
	return (*this = *this * matrix);
}

//! XNAの行列に変換する
XMMATRIX  Matrix::ToXMMATRIX()const {
	return XMLoadFloat4x4(this);
}

//! クォータニオンに変換する
Quaternion Matrix::ToQuaternion()const {
	// 最大成分を検索
	float elem[4]; // 0:x, 1:y, 2:z, 3:w
	elem[0] = _11 - _22 - _33 + 1.0f;
	elem[1] = -_11 + _22 - _33 + 1.0f;
	elem[2] = -_11 - _22 + _33 + 1.0f;
	elem[3] = _11 + _22 + _33 + 1.0f;

	unsigned biggestIndex = 0;
	for (int i = 1; i < 4; i++) {
		if (elem[i] > elem[biggestIndex])
			biggestIndex = i;
	}

	if (elem[biggestIndex] < 0.0f)
		return Quaternion(); // 引数の行列に間違いあり！

	// 最大要素の値を算出
	Quaternion q;
	float v = sqrtf(elem[biggestIndex]) * 0.5f;

	float mult = 0.25f / v;

	switch (biggestIndex) {
		case 0: // x
			q.x = v;
			q.y = (_12 + _21) * mult;
			q.z = (_31 + _13) * mult;
			q.w = (_32 - _23) * mult;
			break;
		case 1: // y
			q.x = (_12 + _21) * mult;
			q.y = v;
			q.z = (_23 + _32) * mult;
			q.w = (_13 - _31) * mult;
			break;
		case 2: // z
			q.x = (_31 + _13) * mult;
			q.y = (_23 + _32) * mult;
			q.z = v;
			q.w = (_21 - _12) * mult;
			break;
		case 3: // w
			q.x = (_32 - _23) * mult;
			q.y = (_13 - _31) * mult;
			q.z = (_21 - _12) * mult;
			q.w = v;
			break;
	}
	return q;
}

const Matrix& Matrix::Transpose() {
	return *this = Transposed();
}

Matrix& Matrix::Inverse() {
	return *this = Inversed();
}

Matrix Matrix::Transposed()const {
	return XMMatrixTranspose(ToXMMATRIX());
}

Matrix Matrix::Inversed() {
	return XMMatrixInverse(nullptr, ToXMMATRIX());
}

//!*******************************************************
//!	[メソッド] static　メソッド

//! 平行移動行列を生成する
Matrix Matrix::CreateTranslate(float x, float y, float z) {
	return Matrix(XMMatrixTranslation(x, y, z));
}

Matrix Matrix::CreateTranslate(const Vector3& offset) {
	return Matrix::CreateTranslate(offset.x, offset.y, offset.z);
}

//! 回転行列を生成する
Matrix Matrix::CreateRotate(const Quaternion& q) {
	return Matrix(XMMatrixRotationQuaternion(q.ToXMVECTOR()));
}

//! 拡縮行列を生成する
Matrix Matrix::CreateScale(float x, float y, float z) {
	return Matrix(XMMatrixScaling(x, y, z));
}

Matrix Matrix::CreateScale(const Vector3& scale) {
	return Matrix::CreateScale(scale.x, scale.y, scale.z);
}

Matrix Matrix::CreateLookAt(const Vector3& eye, const Vector3& at, const Vector3& up) {
	return Matrix(XMMatrixLookAtLH(eye.ToXMVECTOR(), at.ToXMVECTOR(), up.ToXMVECTOR()));
}

Vector3 Matrix::TransformCoord(const Vector3&v) {
	return XMVector3TransformCoord(v.ToXMVECTOR(), ToXMMATRIX());
}
Vector3	Matrix::TransformVector(const Vector3&v) {
	return Vector3(XMVector3Transform(v.ToXMVECTOR(), ToXMMATRIX()));
}
Vector3 Matrix::TransformPoint(const Vector3&v) {
	Vector3 result;
	result.x = v.x * m[0][0] +
		v.y * m[1][0] +
		v.z * m[2][0] +
		m[3][0];

	result.y = v.x * m[0][1] +
		v.y * m[1][1] +
		v.z * m[2][1] +
		m[3][1];

	result.z = v.x * m[0][2] +
		v.y * m[1][2] +
		v.z * m[2][2] +
		m[3][2];

	return result;
}
Vector4 Matrix::TransformVector(const Vector4&v) {
	return Vector4(XMVector4Transform(v.ToXMVECTOR(), ToXMMATRIX()));
}
bool Matrix::operator==(const Matrix& matrix) {
	return  m[0][0] == matrix.m[0][0] &&
		m[0][1] == matrix.m[0][1] &&
		m[0][2] == matrix.m[0][2] &&
		m[0][3] == matrix.m[0][3] &&
		m[1][0] == matrix.m[1][0] &&
		m[1][1] == matrix.m[1][1] &&
		m[1][2] == matrix.m[1][2] &&
		m[1][3] == matrix.m[1][3] &&
		m[2][0] == matrix.m[2][0] &&
		m[2][1] == matrix.m[2][1] &&
		m[2][2] == matrix.m[2][2] &&
		m[2][3] == matrix.m[2][3] &&
		m[3][0] == matrix.m[3][0] &&
		m[3][1] == matrix.m[3][1] &&
		m[3][2] == matrix.m[3][2] &&
		m[3][3] == matrix.m[3][3];
}

bool Matrix::operator!=(const Matrix& matrix) {
	return !(*this == matrix);
}