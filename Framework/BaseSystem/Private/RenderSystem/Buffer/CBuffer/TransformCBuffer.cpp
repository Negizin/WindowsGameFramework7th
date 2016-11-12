#include "TransformCBuffer.h"

#include	"../../DX11Device/DeviceContext.h"
#include	"../../../../../GameObjectClasses/Camera/Camera.h"

TransformCBuffer::TransformCBuffer()
	:m_pTransform(nullptr) {
}

bool TransformCBuffer::UpdateCBuffer(DeviceContext * pContext) {
	if (m_pTransform) {
		Matrix&& mtxWorld = m_pTransform->ToWorldMatrix();
		//if (m_matrixCash != mtxWorld){
		m_matrixCBuffer.m_MtxOldWorld = m_matrixCBuffer.m_MtxWorld;
		m_matrixCBuffer.m_MtxInvOldWorld = m_matrixCBuffer.m_MtxInvWorld;
		m_matrixCBuffer.m_MtxWorld = mtxWorld.Transposed();
		m_matrixCBuffer.m_MtxInvWorld = mtxWorld.Inversed().Transposed();
		pContext->ChangeCBuffer(this, &m_matrixCBuffer, sizeof(m_matrixCBuffer));
		m_matrixCash = mtxWorld;
	//}
	}
	else {
		return FALSE;
	}

	return TRUE;

}
bool TransformCBuffer::ApplyCBuffer(DeviceContext * pContext) {
	pContext->SetCBuffer(this);
	return TRUE;
}
bool TransformCBuffer::CreateTransformCBuffer(DX11Device* pDev) {

	this->CreateCBuffer(pDev, &m_matrixCBuffer, sizeof(m_matrixCBuffer));
	SetRegisterIndex(0);
	BindShaderType(SHADER_TYPE::VERTEX_SHADER);
	return TRUE;
}

bool TransformCBuffer::SetTransform(Transform* pTransform) {
	m_pTransform = pTransform;
	return TRUE;
}