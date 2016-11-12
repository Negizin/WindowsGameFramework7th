#pragma once

#include "CBuffer.h"
#include	"../../../../../Utilities/Math/Math.h"


class Skeleton;
class BoneCBuffer :public CBuffer {
public:
	BoneCBuffer();
	virtual bool UpdateCBuffer(DeviceContext * pContext) override;
	virtual bool ApplyCBuffer(DeviceContext * pContext) override;
	bool CreateBoneCBuffer(DX11Device* pDev);
	void SetSkeleton(Skeleton *pskeleton);
protected:
	struct BoneMatrixCBuffer {
		Matrix bone[764];
	};
	Skeleton *m_pSkeleton;
	BoneMatrixCBuffer m_boneCBuffer;
};