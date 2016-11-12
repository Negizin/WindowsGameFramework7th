//!*******************************************************
//!	TsGeometryObject.h
//!
//!	Mesh base.
//!

#pragma once
#include "DrawObject.h"
#include	"../Buffer/CBuffer/TransformCBuffer.h"
#include "../Mesh/Mesh.h"
#include "../Material/MaterialBase.h"


class DX11Device;

class GeometryObject : virtual public DrawObject {
public:
	GeometryObject();
	virtual ~GeometryObject();
	virtual bool CreateGeometryObject(DX11Device* pDev,
		Mesh * pMesh,
		MaterialBase* pMaterial);

	virtual bool UpdateTransform(DeviceContext* context)override;
	virtual bool UpdateMaterial(DeviceContext* context)override;
	virtual bool UpdateIndexBuffer(DeviceContext* context)override;
	virtual bool UpdateVertexBuffer(DeviceContext* context)override;

	virtual bool ApplyTransForm(DeviceContext * context)override;
	virtual bool ApplyMaterial(DeviceContext* context)override;
	virtual bool ApplyIndexBuffer(DeviceContext* context)override;
	virtual bool ApplyVertexBuffer(DeviceContext* context)override;
	virtual bool Draw(DeviceContext*)override;

	bool SetMaterial(MaterialBase* pMaterial);
	bool SetTransform(Transform * pTransform);
	bool SetMesh(Mesh*);
protected:
	Transform*		m_transform;
	Mesh*				m_mesh;
	MaterialBase*			m_material;
	TransformCBuffer* m_transformCBuffer;
};