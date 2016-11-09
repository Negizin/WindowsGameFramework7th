#include "Vector.h"

const Vector2 Vector2::zero = Vector2(0, 0);
const Vector2 Vector2::one = Vector2(1, 1);
const Vector2 Vector2::up = Vector2(0, 1);
const Vector2 Vector2::down = Vector2(0, -1);
const Vector2 Vector2::left = Vector2(-1, 0);
const Vector2 Vector2::right = Vector2(1, 0);

Vector2& Vector2::operator = (const XMVECTOR& Float2) {
	this->x = Float2.m128_f32[0];
	this->y = Float2.m128_f32[1];
	return *this;
}

Vector2  Vector2::operator+ (const XMFLOAT2& Float2)const {
	return Vector2(x + Float2.x, y + Float2.y);
}
Vector2  Vector2::operator- (const XMFLOAT2& Float2)const {
	return Vector2(x - Float2.x, y - Float2.y);
}
Vector2  Vector2::operator* (float Float)const {
	return Vector2(x*Float, y*Float);
}
Vector2  Vector2::operator/ (float Float)const {
	return Vector2(x / Float, y / Float);
}
Vector2& Vector2::operator+= (const XMFLOAT2& Float2) {
	return *this = *this + Float2;
}
Vector2& Vector2::operator-= (const XMFLOAT2& Float2) {
	return *this = *this - Float2;
}
Vector2& Vector2::operator*= (float Float) {
	return *this = *this * Float;
}
Vector2& Vector2::operator/= (float Float) {
	return *this = *this / Float;
}
bool Vector2::operator==(const Vector2& value)const {
	return x == value.x &&
		y == value.y;
}
bool Vector2::operator!=(const Vector2& value)const {
	return !(*this == value);
}
bool Vector2::operator>=(const Vector2& value)const {
	return x >= value.x && y >= value.y;
}
bool Vector2::operator<=(const Vector2& value)const {
	return x <= value.x && y <= value.y;
}
bool Vector2::operator>(const Vector2& value)const {
	return x > value.x && y > value.y;
}
bool Vector2::operator<(const Vector2& value)const {
	return x < value.x && y < value.y;
}
XMVECTOR Vector2::ToXMVECTOR()const {
	return XMLoadFloat2(this);
}

float Vector2::Length()const {
	XMVECTOR vLength = XMVector2Length(ToXMVECTOR());
	return (vLength.m128_f32[0] + vLength.m128_f32[1]);
}

Vector2& Vector2::Normalize() {
	*this = Normalized();
	return *this;
}
Vector2 Vector2::Normalized()const {
	return Vector2(XMVector2Normalize(ToXMVECTOR()));
}


float Vector2::Dot(Vector2 v0,
	Vector2 v1) {
	return XMVector2Dot(v0.ToXMVECTOR(), v1.ToXMVECTOR()).m128_f32[0];
}

Vector2 Vector2::Closs(Vector2 v0,
	Vector2 v1) {
	return Vector2(XMVector2Cross(v0.ToXMVECTOR(), v1.ToXMVECTOR()));
}


