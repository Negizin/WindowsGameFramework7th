#include "LambertMaterial.h"
#include	"../DX11Device/DX11Device.h"

LambertMatrial::LambertMatrial()
{

};

LambertMatrial::~LambertMatrial()
{

};

bool LambertMatrial::SetColor(std::array<float, 4> color)
{
	m_material.diffuse = color;
	m_isUpdate = TRUE;
	return TRUE;
}

bool LambertMatrial::CreateMaterial(DX11Device* pDev)
{
	//コンスタントバッファー作成
	this->CreateCBuffer(pDev, &m_material, sizeof(m_material));
	SetRegisterIndex(1);	//register Index = [c1]
	BindShaderType(SHADER_TYPE::PIXEL_SHADER);
	return TRUE;
}

bool LambertMatrial::ApplyMaterial(DeviceContext* pContext)
{
	pContext->SetCBuffer(this);
	pContext->SetTexture(0, m_pTexture, SHADER_TYPE::PIXEL_SHADER);
	return TRUE;
}

bool LambertMatrial::UpdateMaterial(DeviceContext* pContext)
{
	if (m_isUpdate)
		pContext->ChangeCBuffer(this, &m_material, GetBufferSize());
	m_isUpdate = FALSE;
	return TRUE;
}