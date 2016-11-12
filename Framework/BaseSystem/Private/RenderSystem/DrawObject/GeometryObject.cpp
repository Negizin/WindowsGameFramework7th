#include "GeometryObject.h"
#include "../DX11Device/DX11Device.h"

GeometryObject::GeometryObject() :
	m_material(nullptr),
	m_mesh(nullptr),
	m_transform(nullptr),
	m_transformCBuffer(nullptr) {
}

GeometryObject::~GeometryObject() {
	SafeDelete(m_transform);
	SafeDelete(m_transformCBuffer);
}

bool GeometryObject::CreateGeometryObject(DX11Device* pDev,
	Mesh * pMesh,
	MaterialBase* pMaterial) {
	SetMesh(pMesh);
	SetMaterial(pMaterial);

	m_transform = new Transform();
	m_transformCBuffer = new TransformCBuffer;

	m_transformCBuffer->CreateTransformCBuffer(pDev);
	m_transformCBuffer->SetTransform(m_transform);

	return TRUE;
}

bool GeometryObject::UpdateTransform(DeviceContext* context) {
	if (m_transformCBuffer)
		m_transformCBuffer->UpdateCBuffer(context);
	else
		return FALSE;
	return TRUE;
}
bool GeometryObject::UpdateMaterial(DeviceContext* context) {
	if (m_material)
		m_material->UpdateMaterial(context);
	else
		return FALSE;
	return TRUE;
}
bool GeometryObject::UpdateIndexBuffer(DeviceContext* context) {
	(void) context;
	return TRUE;
}
bool GeometryObject::UpdateVertexBuffer(DeviceContext* context) {
	(void) context;
	return TRUE;
}

bool GeometryObject::ApplyTransForm(DeviceContext * context) {
	if (m_transformCBuffer)
		m_transformCBuffer->ApplyCBuffer(context);
	else
		return FALSE;
	return TRUE;
}
bool GeometryObject::ApplyMaterial(DeviceContext* context) {
	if (m_material)
		m_material->ApplyMaterial(context);
	else
		return FALSE;
	return TRUE;
}
bool GeometryObject::ApplyIndexBuffer(DeviceContext* context) {
	if (m_mesh) {
		IndexBuffer * pIb = m_mesh->GetIndexBuffer();
		if (pIb)
			context->SetIndexBuffer(pIb);
		else
			return FALSE;
	}
	else
		return FALSE;
	return TRUE;
}
bool GeometryObject::ApplyVertexBuffer(DeviceContext* context) {
	if (m_mesh)
		context->SetVertexBuffer(m_mesh->GetVertexBuffer());
	else
		return FALSE;
	return TRUE;
}
bool GeometryObject::Draw(DeviceContext* context) {
	if (m_mesh) {
		//todo debug
		context->SetTopology(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		context->Draw(m_mesh->GetVertexNum());
	}
	else
		return FALSE;
	return TRUE;
}

bool GeometryObject::SetMaterial(MaterialBase* pMaterial) {
	m_material = pMaterial;
	return TRUE;
}
bool GeometryObject::SetMesh(Mesh* pMesh) {
	m_mesh = pMesh;
	return TRUE;
}