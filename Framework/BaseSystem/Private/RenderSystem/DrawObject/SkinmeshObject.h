//!*******************************************************
//!	TsGeometryObject.h
//!
//!	Mesh base.
//!

#pragma once
#include "GeometryObject.h"
#include "../Buffer/CBuffer/TransformCBuffer.h"
#include "../Mesh/SkinMesh.h"
#include "../Material/PmxMaterialBase.h"
#include "../Buffer/CBuffer/BoneCBuffer.h"
#include <vector>

class DX11Device;

class SkinMeshObject : virtual public GeometryObject {
public:
	SkinMeshObject();
	virtual ~SkinMeshObject();
	bool CreateGeometryObject(DX11Device* pDev,
		Mesh * pMesh,
		PmxMaterialBase* pMaterial);

	virtual bool UpdateTransform(DeviceContext* context)override;

	virtual bool ApplyTransForm(DeviceContext * context)override;

	virtual bool Draw(DeviceContext*)override;

	bool SetMaterial(PmxMaterialBase* pMaterial);

	bool SetSkeleton(Skeleton * pSkeleton);

private:
	Skeleton *m_pSkeleton;
	std::vector<PmxMaterialBase*>	m_material;
	BoneCBuffer * m_boneCBuffer;
};