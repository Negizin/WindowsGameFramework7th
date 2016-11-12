#include "Bone.h"
#include	"../../../../../Utilities/../ComponentClasses/Transform/Transform.h"

Bone::Bone() {
}

Bone::~Bone() {
}

bool Bone::ComputeBoneMatrix() {
	m_boneMatrix = (m_invBindPoseMatrix * m_pTransform->ToWorldMatrix());
	return true;
}

int Bone::GetBoneID() {
	return m_boneID;
}

Transform *Bone::GetTransform() {
	return m_pTransform;
}

bool Bone::SetBindPoseMatrix(const Matrix& bindPoseMatrix) {

	m_bindPoseMatrix = bindPoseMatrix;
	m_invBindPoseMatrix = m_bindPoseMatrix.Inversed();
	return true;
}

bool Bone::SetBoneID(int boneID) {
	m_boneID = boneID;
	return true;
}

const Matrix& Bone::GetBoneMatrix() {
	return m_boneMatrix;
}