#include	"Vector.h"
#include	"../Matrix/Matrix.h"
#include	"../Math.h"

const  Vector3  Vector3::zero = Vector3(0, 0, 0);
const  Vector3  Vector3::one = Vector3(1, 1, 1);
const  Vector3  Vector3::up = Vector3(0, 1, 0);
const  Vector3  Vector3::down = Vector3(0, -1, 0);
const  Vector3  Vector3::left = Vector3(-1, 0, 0);
const  Vector3  Vector3::right = Vector3(1, 0, 0);
const  Vector3  Vector3::front = Vector3(0, 0, 1);
const  Vector3  Vector3::back = Vector3(0, 0, -1);

Vector3&  Vector3::operator = (const XMVECTOR& float3) {
	this->x = float3.m128_f32[0];
	this->y = float3.m128_f32[1];
	this->z = float3.m128_f32[2];
	return *this;
}

Vector3   Vector3::operator+ (const XMFLOAT3& float3)const {
	return  Vector3(x + float3.x, y + float3.y, z + float3.z);
}
Vector3   Vector3::operator- (const XMFLOAT3& float3)const {
	return  Vector3(x - float3.x, y - float3.y, z - float3.z);
}
Vector3   Vector3::operator* (float FLOAT)const {
	return  Vector3(x * FLOAT, y * FLOAT, z * FLOAT);
}
Vector3   Vector3::operator/ (float FLOAT)const {
	return  Vector3(x / FLOAT, y / FLOAT, z / FLOAT);
}

Vector3&  Vector3::operator+= (const XMFLOAT3& float3) {
	return *this = *this + float3;
}
Vector3&  Vector3::operator-= (const XMFLOAT3& float3) {
	return *this = *this - float3;
}
Vector3&  Vector3::operator*= (float FLOAT) {
	return *this = *this * FLOAT;
}
Vector3&  Vector3::operator/= (float FLOAT) {
	return *this = *this / FLOAT;
}

Vector3   Vector3::operator*(const  Matrix& mat)const {
	return  Vector3(XMVector3Transform(ToXMVECTOR(), mat.ToXMMATRIX()));
}
Vector3&  Vector3::operator*=(const  Matrix& mat) {
	return *this = *this * mat;
}

bool  Vector3::operator==(const  Vector3& value)const {
	return	x == value.x &&
		y == value.y &&
		z == value.z;
}
bool  Vector3::operator!=(const  Vector3& value)const {
	return !(*this == value);
}
bool  Vector3::operator>=(const  Vector3& value)const {
	return x >= value.x && y >= value.y && z >= value.z;
}
bool  Vector3::operator<=(const  Vector3& value)const {
	return x <= value.x && y <= value.y && z <= value.z;
}
bool  Vector3::operator>(const  Vector3& value)const {
	return x > value.x && y > value.y && z > value.z;
}
bool  Vector3::operator<(const  Vector3& value)const {
	return x < value.x && y < value.y && z >value.z;
}
Vector3&  Vector3::TransformCood(const  Matrix& mat) {
	return 	*this = XMVector3TransformCoord(ToXMVECTOR(), mat.ToXMMATRIX());
}
XMVECTOR  Vector3::ToXMVECTOR()const {
	return XMLoadFloat3(this);
}

float  Vector3::Length()const {
	XMVECTOR vLength = XMVector3Length(ToXMVECTOR());
	return (vLength.m128_f32[0]);
}

const Vector3&  Vector3::Normalize() {
	*this = Normalized();
	return *this;
}
Vector3  Vector3::Normalized()const {
	return  Vector3(XMVector3Normalize(ToXMVECTOR()));
}

float  Vector3::Dot(Vector3 v0,
	Vector3 v1) {
	return XMVector3Dot(v0.ToXMVECTOR(), v1.ToXMVECTOR()).m128_f32[0];
}

Vector3  Vector3::Cross(Vector3 v0,
	Vector3 v1) {
	return  Vector3(XMVector3Cross(v0.ToXMVECTOR(), v1.ToXMVECTOR()));
}

float  Vector3::CrossingAngle(Vector3 v0, Vector3 v1) {
	float d = v0.Length() * v1.Length();

	if (d == 0)return 0;

	float c = Dot(v0, v1) / d;

	if (c >= 1.0) return 0;
	if (c <= -1.0) return  Math::PI;

	return acos(c);
}