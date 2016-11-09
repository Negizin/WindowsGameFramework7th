#include "RenderFlow.h"
#include "RenderPass.h"
#include "DrawQueue.h"
#include "ClearPass.h"


bool RenderFlow::Render(DeviceContext * pDc, DrawQueue *Queue) {
	if (pDc == nullptr || Queue == nullptr)
		return FALSE;

	for (auto it : m_renderPass) {
		it->Begin(pDc);
		it->Render(Queue, pDc);
		it->End(pDc);
	}
	return TRUE;
}

RenderPass* RenderFlow::GetPipeLine(tstring name) {
	HASH hash = UT::StringToHash(name);

	for (auto it : m_renderPass) {
		if (it->GetHashCode() == hash)
			return it;
	}

	return nullptr;
}


RenderPass* RenderFlow::GetPipeLine(int index) {
	if ((unsigned) index > m_renderPass.size())
		return nullptr;
	else
		return m_renderPass[index];
}

bool RenderFlow::SetPipeLine(RenderPass* pass, int index) {
	if ((unsigned) index >= m_renderPass.size())
		m_renderPass.push_back(pass);
	else
		m_renderPass[index] = pass;

	return TRUE;
}

int RenderFlow::GetFlowSize() {
	return m_renderPass.size();
}

bool RenderFlow::LoadFlomXML(DX11Device *pDev, const tstring& file) {

	XML xml;
	xml.LoadXML(UT::Resource::GetShaderFlowDirectory() + file);
	auto elm = xml.GetRootNode()->GetFirstChild();
	while (elm != nullptr) {
		if (elm->GetName() == _T("Pass")) {
			tstring passName = elm->GetAttribute(_T("Name"))->GetStringValue();
			RenderPass* pRenderpass;
			if (passName == _T("Clear")) {
				pRenderpass = new ClearPass();
			}
			else {
				pRenderpass = new RenderPass();
			}
			pRenderpass->SetName(passName);
			pRenderpass->LoadShaderFromXMLElement(pDev, elm);
			pRenderpass->LoadIOSlotFromXMLElement(pDev, elm);

			m_renderPass.push_back(pRenderpass);
		}
		elm = elm->Next();
	}
	return true;
}