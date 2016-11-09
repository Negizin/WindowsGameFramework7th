#include	"Effect.h"
#include	"../Utilities/XML/Xml.h"
#include	"../DX11Device/DX11Device.h"
#include	"../State/DepthStencilState.h"
#include	"../State/RasterizerState.h"

bool	Effect::SetVertexShader(VertexShader* shader) {
	m_vertexShader = shader;
	return TRUE;
}
bool	Effect::SetPixelShader(PixelShader* shader) {
	m_pixelShader = shader;
	return TRUE;
}
bool	Effect::SetGeometryShader(GeometryShader* shader) {
	m_geometoryShader = shader;
	return TRUE;
}
bool	Effect::SetHullShader(HullShader* shader) {
	m_hullShader = shader;
	return TRUE;
}
bool	Effect::SetDomainShader(DomainShader* shader) {
	m_domainShader = shader;
	return TRUE;
}
bool	Effect::SetComputeShader(ComputeShader* shader) {
	m_computeShader = shader;
	return TRUE;
}

ID3D11InputLayout* Effect::GetInputLayout() {
	if (m_vertexShader == nullptr)
		return nullptr;
	return m_vertexShader->GetInputLayout();
}

bool Effect::LoadPackageFromXml(DX11Device *pDev, const tstring& file) {
	XML xmlshaderpass;
	xmlshaderpass.LoadXML(UT::Resource::GetShaderPackageDirectory() + file);

	auto name = xmlshaderpass.FindFirst(_T("Name"))->GetAttribute(_T("Name"))->GetStringValue();
	SetName(name);

	auto ShaderDir = UT::Resource::GetCSODirectory();

	tstring ShaderName;
	MyXMLElement* elm = xmlshaderpass.FindFirst(_T("Vertex"));

	if (elm != nullptr) {
		ShaderName = elm->GetAttribute(_T("Shader"))->GetStringValue() + _T(".cso");
		VertexShader *pVS = new VertexShader();
		bool hr = pVS->LoadFromCSO(pDev->GetDevD3D(), (ShaderDir + ShaderName).c_str());

		SetVertexShader(pVS);
	}

	elm = xmlshaderpass.FindFirst(_T("Pixel"));

	if (elm != nullptr) {
		ShaderName = elm->GetAttribute(_T("Shader"))->GetStringValue() + _T(".cso");
		PixelShader *pPS = new PixelShader();
		pPS->LoadFromCSO(pDev->GetDevD3D(), (ShaderDir + ShaderName).c_str());
		SetPixelShader(pPS);
	}

	elm = xmlshaderpass.FindFirst(_T("DepthStencil"));
	m_pDepthStencilState = new DepthStencilState();

	if (elm != nullptr) {
		MyXMLAttribute* pAttr = elm->GetAttribute(_T("ZEnable"));
		if (pAttr) {
			bool zEnable = pAttr->GetBoolValue();
			m_pDepthStencilState->SetZEnable(zEnable);
		}
		pAttr = elm->GetAttribute(_T("ZWriteEnable"));
		if (pAttr) {
			bool zWriteEnable = pAttr->GetBoolValue();
			m_pDepthStencilState->SetZWriteEnable(zWriteEnable);
		}
		pAttr = elm->GetAttribute(_T("Func"));
		if (pAttr) {
			tstring depthTestFunc = pAttr->GetStringValue();
			m_pDepthStencilState->SetDepthTestFunctionByString(depthTestFunc);
		}
	}
	m_pDepthStencilState->CreateDepthStencilState(pDev);
	elm = xmlshaderpass.FindFirst(_T("Rasterize"));
	m_pRasterizerState = new RasterizerState();

	if (elm != nullptr) {
		MyXMLAttribute* pAttr = elm->GetAttribute(_T("FillMode"));
		if (pAttr) {
			tstring fillmode = pAttr->GetStringValue();
			m_pRasterizerState->SetFillModeByString(fillmode);
		}
		pAttr = elm->GetAttribute(_T("CullMode"));
		if (pAttr) {
			tstring cullmode = pAttr->GetStringValue();
			m_pRasterizerState->SetCullModeByString(cullmode);
		}
		pAttr = elm->GetAttribute(_T("Func"));
		if (pAttr) {
			bool  AntiAlias = pAttr->GetBoolValue();
			m_pRasterizerState->SetAnitiAliasMode(AntiAlias);
		}
	}
	m_pRasterizerState->CreateRasterizerState(pDev);

	return true;
}