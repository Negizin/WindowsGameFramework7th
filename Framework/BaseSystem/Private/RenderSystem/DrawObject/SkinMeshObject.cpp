#include "SkinMeshObject.h"
#include "../DX11Device/DX11Device.h"

SkinMeshObject::SkinMeshObject() :
	m_boneCBuffer(nullptr),
	m_pSkeleton(nullptr) {
	this->m_material.resize(0);
}

SkinMeshObject::~SkinMeshObject() {

	SafeDelete(m_boneCBuffer);

}

bool SkinMeshObject::CreateGeometryObject(DX11Device* pDev,
	Mesh * pMesh,
	PmxMaterialBase* pMaterial) {
	GeometryObject::CreateGeometryObject(pDev, pMesh, pMaterial);

	m_boneCBuffer = new BoneCBuffer;
	m_boneCBuffer->CreateBoneCBuffer(pDev);
	return TRUE;
}

bool SkinMeshObject::UpdateTransform(DeviceContext* context) {

	GeometryObject::UpdateTransform(context);
	if (m_boneCBuffer)
		m_boneCBuffer->UpdateCBuffer(context);
	else
		return FALSE;
	return TRUE;
}

bool SkinMeshObject::ApplyTransForm(DeviceContext * context) {
	GeometryObject::ApplyTransForm(context);
	if (m_boneCBuffer)
		m_boneCBuffer->ApplyCBuffer(context);
	else
		return FALSE;
	return TRUE;
}


bool SkinMeshObject::Draw(DeviceContext* context) {

	if (m_mesh) {
		//todo debug
		int startindex = 0;

		for (unsigned int i = 0; i < this->m_material.size(); ++i) {
			//D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
			//D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
			context->SetTopology(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			m_material[i]->ApplyMaterial(context);
			m_material[i]->UpdateMaterial(context);
			context->DrawIndex(startindex, m_material[i]->GetMaterialMeshCount());
			startindex += m_material[i]->GetMaterialMeshCount();
		}

	}
	else
		return FALSE;
	return TRUE;
}

bool SkinMeshObject::SetMaterial(PmxMaterialBase* pMaterial) {
	m_material.push_back(pMaterial);
	return TRUE;
}

bool SkinMeshObject::SetSkeleton(Skeleton *pSkeleton) {
	m_pSkeleton = pSkeleton;
	return true;
}