#pragma once

#include	"CBuffer.h"
#include	"../../../../../Utilities/Math/Math.h"
#include	"../../../../../ComponentClasses/Transform/Transform.h"

class TransformCBuffer :public CBuffer {
public:
	TransformCBuffer();
	virtual bool UpdateCBuffer(DeviceContext * pContext) override;
	virtual bool ApplyCBuffer(DeviceContext * pContext) override;
	bool CreateTransformCBuffer(DX11Device* pDev);
	bool SetTransform(Transform* pTransform);
protected:
	struct MatrixCBuffer {
		Matrix m_MtxWorld;
		Matrix m_MtxOldWorld;
		Matrix m_MtxInvWorld;
		Matrix m_MtxInvOldWorld;
	};

	Transform* m_pTransform;
	Matrix	 m_matrixCash;
	MatrixCBuffer m_matrixCBuffer;
};