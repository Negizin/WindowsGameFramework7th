#include "BoneCBuffer.h"

#include	"../../DX11Device/DeviceContext.h"
#include	"../../Utilities/Skeleton/Skeleton.h"
#include	"../../Utilities/Bone/Bone.h"

BoneCBuffer::BoneCBuffer() :m_pSkeleton(nullptr) {
}

bool BoneCBuffer::UpdateCBuffer(DeviceContext * pContext) {
	if (m_pSkeleton == nullptr)
		return false;
	std::vector<Bone*> &bonelist = m_pSkeleton->GetBoneArray();
	for each(auto pBone in bonelist) {
		m_boneCBuffer.bone[pBone->GetBoneID()] = pBone->GetBoneMatrix().Transposed();
	}

	pContext->ChangeCBuffer(this, &m_boneCBuffer, sizeof(BoneMatrixCBuffer));


	return TRUE;

}
bool BoneCBuffer::ApplyCBuffer(DeviceContext * pContext) {
	if (m_pSkeleton == nullptr)
		return false;
	pContext->SetCBuffer(this);
	return TRUE;
}

bool BoneCBuffer::CreateBoneCBuffer(DX11Device* pDev) {

	this->CreateCBuffer(pDev, &m_boneCBuffer, sizeof(BoneMatrixCBuffer));
	SetRegisterIndex(1);
	BindShaderType(SHADER_TYPE::VERTEX_SHADER);

	return TRUE;
}

void BoneCBuffer::SetSkeleton(Skeleton *pskeleton) {
	m_pSkeleton = pskeleton;
}
