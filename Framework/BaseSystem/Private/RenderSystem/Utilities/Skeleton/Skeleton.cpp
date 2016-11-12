#include "Skeleton.h"
#include "../Bone/Bone.h"
#include	"../../../../../ComponentClasses/Transform/Transform.h"

Skeleton::Skeleton() {
}

Skeleton::~Skeleton() {
	for each(auto it in m_pboneArray)
		SafeDelete(it);
}


bool Skeleton::AddBone(Transform* pTransform,
	int boneID,
	const Matrix& bindPoseMatrix,
	Transform* pRootBone) {
	Bone* pBone = new Bone();
	pBone->SetBindPoseMatrix(bindPoseMatrix);
	pBone->m_pTransform = pTransform;
	pBone->SetBoneID(boneID);
	pBone->m_pRootBone = pRootBone;
	m_pboneArray.push_back(pBone);
	return true;
}


bool Skeleton::UpdateSkeleton() {
	if (m_isUpdate == false) {
		for (unsigned int i = 0; i < m_pboneArray.size(); ++i)
			m_pboneArray[i]->ComputeBoneMatrix();
	}
	m_isUpdate = true;
	return true;
}

std::vector<Bone *>& Skeleton::GetBoneArray() {
	return m_pboneArray;
}