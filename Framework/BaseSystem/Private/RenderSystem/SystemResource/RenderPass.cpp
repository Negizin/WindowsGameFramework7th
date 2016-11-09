#include "RenderPass.h"
#include "DrawQueue.h"
#include "RenderFlow.h"

#include	"../Effect/Effect.h"
#include	"../ShaderResource/Texture/RenderTarget/RenderTarget.h"
#include	"../ShaderResource/Texture/DepthStencil/DepthStencil.h"
#include	"../ResourceManager/ResourceManager.h"
#include	"../Utilities/XML/Xml.h"

RenderPass::RenderPass() :
	m_pDepthStencil(nullptr),
	m_pShader(nullptr),
	m_pRasterizerState(nullptr),
	m_pDepthStencilState(nullptr) {
	for (int i = 0; i < DeviceContext::MAX_RTs; ++i) {
		m_pInputSlot[i] = nullptr;
		m_pOutputSlot[i] = nullptr;
	}
}
RenderPass::~RenderPass() {

}

bool RenderPass::SetDepthSlot(DepthStencil *pDepth) {
	m_pDepthStencil = pDepth;
	return true;
}

bool RenderPass::ApplyRTV(DeviceContext * pDC) {
	for (int i = 0; i < DeviceContext::MAX_RTs; ++i)
		pDC->SetRT(i, m_pOutputSlot[i]);
	pDC->SetDepthStencil(m_pDepthStencil);
	pDC->ApplyRenderTargets();
	return true;
}

bool RenderPass::Render(DrawQueue *pQueue, DeviceContext*pDc) {
	if (pDc == nullptr)
		return false;
	if (pQueue == nullptr)
		return false;

	pQueue->Render(pDc);
	return true;
}

bool RenderPass::Begin(DeviceContext* pDc) {
	//! set render target
	for (int i = 0; i < DeviceContext::MAX_RTs; ++i)
		pDc->SetRT(i, m_pOutputSlot[i]);

	//! set shader
	pDc->SetEffect(m_pShader);
	//! set inputlayout
	pDc->ApplyInputLayout();

	//! SetInputSlot
	for (int i = 0; m_pInputSlot[i] != nullptr; ++i)
		pDc->SetTexture(i, m_pInputSlot[i], SHADER_TYPE::PIXEL_SHADER);

	pDc->SetDepthStencil(m_pDepthStencil);


	return TRUE;
}
bool RenderPass::End(DeviceContext* pDC) {
	for (int i = 0; i < DeviceContext::MAX_RTs; ++i)
		pDC->SetRT(i, nullptr);

	pDC->SetDepthStencil(nullptr);
	return TRUE;
}
bool RenderPass::SetInputSlot(int index, Texture *rtv) {
	if (abs(index) >= DeviceContext::MAX_RTs)
		return FALSE;
	m_pInputSlot[index] = rtv;

	return TRUE;
}

bool RenderPass::SetOutputSlot(int index, RenderTarget *rtv) {
	if (abs(index) >= DeviceContext::MAX_RTs)
		return FALSE;
	m_pOutputSlot[index] = rtv;

	return TRUE;
}

//入力バッファを取得
Texture* RenderPass::GetInputSlot(int index) {
	return m_pInputSlot[index];
}

//出力バッファを取得
RenderTarget* RenderPass::GetOutputSlot(int index /* = 0 */) {
	return m_pOutputSlot[index];
}

bool RenderPass::SetShader(Effect* se) {
	m_pShader = se;

	return TRUE;
}

bool RenderPass::LoadShaderFromXMLElement(DX11Device* pDev, MyXMLElement * pElement) {
	tstring shaderName = pElement->GetAttribute(_T("Shader"))->GetStringValue();
	Effect* pShaderEffect = ResourceManager::Find<Effect>(shaderName);
	if (pShaderEffect == nullptr) {
		pShaderEffect = new Effect;
		pShaderEffect->LoadPackageFromXml(pDev, shaderName + _T(".shaderPackage"));
	}
	m_pDepthStencilState = pShaderEffect->GetDepthStencilState();
	m_pRasterizerState = pShaderEffect->GetRasterizerState();
	SetShader(pShaderEffect);

	return true;
}
bool RenderPass::LoadIOSlotFromXMLElement(DX11Device* pDev, MyXMLElement * pElement) {
	int rtvIndex = 0;
	MyXMLElement* inputSlot = pElement->FindChild(_T("Input"))->GetFirstChild();

	for (; inputSlot != nullptr; inputSlot = inputSlot->Next()) {
		auto slot = inputSlot->GetAttribute(_T("Slot"));
		if (slot == nullptr)
			continue;
		if (inputSlot->GetName() == _T("Slot")) {
			tstring texname = slot->GetStringValue();
			RenderTarget *rtv = nullptr;
			if (texname == _T("Main"))
				rtv = pDev->GetDC()->GetScreenRTV();
			else
				rtv = ResourceManager::Find<RenderTarget>(texname);
			if (rtv != nullptr) {
				SetInputSlot(rtvIndex, rtv);
			}
			else {
				Texture2D* pTex = ResourceManager::Find<Texture2D>(texname);
				if (pTex)
					SetInputSlot(rtvIndex, pTex);
			}
			++rtvIndex;
		}
		else if (inputSlot->GetName() == _T("Depth")) {
			tstring rtName = slot->GetStringValue();
			DepthStencil* dsv = nullptr;
			if (rtName == _T("Main"))
				dsv = pDev->GetDC()->GetMainDSV();
			else
				dsv = ResourceManager::Find<DepthStencil>(rtName);
			SetInputSlot(rtvIndex, dsv);
			++rtvIndex;
		}
	}

	MyXMLElement * outputSlot = pElement->FindChild(_T("Output"))->GetFirstChild();

	rtvIndex = 0;

	for (; outputSlot != nullptr; outputSlot = outputSlot->Next()) {
		auto slot = outputSlot->GetAttribute(_T("Slot"));

		if (slot == nullptr)
			continue;
		tstring rtName = slot->GetStringValue();
		if (outputSlot->GetName() == _T("Slot")) {
			RenderTarget* rtv = nullptr;
			if (rtName == _T("Main"))
				rtv = pDev->GetDC()->GetScreenRTV();
			else
				rtv = ResourceManager::Find<RenderTarget>(rtName);

			SetOutputSlot(rtvIndex, rtv);
			++rtvIndex;
		}
		else if (outputSlot->GetName() == _T("Depth")) {
			DepthStencil* dsv = nullptr;
			if (rtName == _T("Main"))
				dsv = pDev->GetDC()->GetMainDSV();
			else
				dsv = ResourceManager::Find<DepthStencil>(rtName);
			SetDepthSlot(dsv);
		}
	}
	return true;
}