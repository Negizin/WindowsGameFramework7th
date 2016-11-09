#include "Quaternion.h"
#include "../Vector/Vector.h"
#include "../Matrix/Matrix.h"

const Quaternion Quaternion::identity = Quaternion(0, 0, 0, 1);

XMVECTOR Quaternion::ToXMVECTOR()const {
	return XMLoadFloat4(this);
}

Matrix Quaternion::ToMatrix()const {
	return Matrix::CreateRotate(*this);
}


Quaternion  Quaternion::operator * (const Quaternion& quaternion)const {
	return Quaternion(XMQuaternionMultiply(ToXMVECTOR(), quaternion.ToXMVECTOR()));
}

Quaternion& Quaternion::operator *=(const Quaternion& quaternion) {
	return *this = *this * quaternion;
}


Quaternion Quaternion::AngleAxis(Vector3 axis, float angle) {
	return Quaternion(XMQuaternionRotationMatrix(XMMatrixRotationAxis(axis.ToXMVECTOR(), angle)));
}