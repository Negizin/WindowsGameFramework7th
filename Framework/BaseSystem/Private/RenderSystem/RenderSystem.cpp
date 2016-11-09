#include	"RenderSystem.h"
#include	"ShaderResource\Texture\Texture.h"
#include	"DirectXTex\DXTex.h"
#include	"ShaderResource\Texture\RenderTarget\RenderTarget.h"
#include	"ShaderResource\Texture\DepthStencil\DepthStencil.h"
#include	"ResourceManager\ResourceManager.h"

RenderSystem::RenderSystem() {

}

RenderSystem::~RenderSystem() {

}

bool RenderSystem::CallRender(DeviceContext *pDC) {
	m_PreFlowAndQue.Render(pDC);
	m_FlowAndQue.Render(pDC);
	m_PostFlowAndQue.Render(pDC);
	return true;
}

bool RenderSystem::SetDrawQue(DrawQueue *Queue, TARGET_FLOW targetFlow) {
	switch (targetFlow) {
		case TARGET_FLOW::PRE_RENDERER:		m_PreFlowAndQue.m_pQueue = Queue; break;
		case TARGET_FLOW::DEFAULT_RENDERER:		m_FlowAndQue.m_pQueue = Queue; break;
		case TARGET_FLOW::POST_RENDERER:		m_PostFlowAndQue.m_pQueue = Queue; break;
		default:return false;
	}
	return true;
}

bool RenderSystem::SetShaderFlow(RenderFlow* pFlow, TARGET_FLOW targetFlow) {
	switch (targetFlow) {
		case TARGET_FLOW::PRE_RENDERER:		m_PreFlowAndQue.m_pFlow = pFlow; break;
		case TARGET_FLOW::DEFAULT_RENDERER:		m_FlowAndQue.m_pFlow = pFlow; break;
		case TARGET_FLOW::POST_RENDERER:		m_PostFlowAndQue.m_pFlow = pFlow; break;
		default:return false;
	}
	return true;
}

Texture* RenderSystem::FindTextureResource(const tstring& name) {
	HASH hash = UT::StringToHash(name);
	for each(auto it in m_shaderResourceList) {
		if (hash == it->GetHashCode())
			return it;
	}
	return nullptr;
}
bool RenderSystem::LoadRenderSystemFromXML(DX11Device* pDev, const tstring&name) {
	XML xml;
	xml.LoadXML(UT::Resource::GetRenderSystemDirectory() + name);
	auto elm = xml.GetRootNode()->GetFirstChild();
	while (elm != nullptr) {
		//ElementName��Resource�̏ꍇ
		if (elm->GetName() == _T("Resource")) {
			tstring path = elm->GetAttribute(_T("resource"))->GetStringValue();
			UT::FilePathAnalyzer analyze(path);
			if (analyze.GetExtension() == _T(".shaderResource")) {
				LoadShaderResourceFromXML(pDev, path);
			}
		}
		//ElementName��PreRender�̏ꍇ
		else if (elm->GetName() == _T("PreRender")) {
			tstring path = elm->GetAttribute(_T("flow"))->GetStringValue();
			UT::FilePathAnalyzer analyze(path);
			if (analyze.GetExtension() == _T(".shaderflow")) {
				RenderFlow *flow = new RenderFlow();
				flow->LoadFlomXML(pDev, path);
				m_PreFlowAndQue.m_pFlow = flow;
			}
		}
		//ElementName��Render�̏ꍇ
		else if (elm->GetName() == _T("Render")) {
			tstring path = elm->GetAttribute(_T("flow"))->GetStringValue();
			UT::FilePathAnalyzer analyze(path);
			if (analyze.GetExtension() == _T(".shaderflow")) {
				RenderFlow *flow = new RenderFlow();
				flow->LoadFlomXML(pDev, path);
				m_FlowAndQue.m_pFlow = flow;
			}
		}
		//ElementName��PostRender�̏ꍇ
		else if (elm->GetName() == _T("PostRender")) {
			tstring path = elm->GetAttribute(_T("flow"))->GetStringValue();
			UT::FilePathAnalyzer analyze(path);
			if (analyze.GetExtension() == _T(".shaderflow")) {
				RenderFlow *flow = new RenderFlow();
				flow->LoadFlomXML(pDev, path);
				m_PostFlowAndQue.m_pFlow = flow;
			}
		}
		elm = elm->Next();
	}
	return true;
}
bool RenderSystem::LoadShaderResourceFromXML(DX11Device* pDev, const tstring& name) {
	XML xml;
	xml.LoadXML(UT::Resource::GetShaderResourceDirectory() + name);
	auto elm = xml.GetRootNode()->GetFirstChild();
	while (elm != nullptr) {
		//ElementName��Texture�̏ꍇ
		if (elm->GetName() == _T("Texture")) {
			Texture2D *pTexture = new Texture2D();
			tstring name = elm->GetAttribute(_T("Name"))->GetStringValue();
			tstring path = elm->GetAttribute(_T("Path"))->GetStringValue();
			auto srv = DXTex::LoadFromFile(pDev->GetDevD3D(), path.c_str());

			pTexture->SetName(name);
			pTexture->SetSRV(srv);

			m_shaderResourceList.push_back(pTexture);
			ResourceManager::RegisterResource<Texture2D>(pTexture, name);

		}
		//ElementName��RenderTarget�̏ꍇ
		if (elm->GetName() == _T("RenderTarget")) {

			tstring name = elm->GetAttribute(_T("Name"))->GetStringValue();
			tstring format = elm->GetAttribute(_T("Format"))->GetStringValue();
			auto size = elm->GetAttribute(_T("Size"))->GetInt2Value();

			if (size[0] < 0)
				size = pDev->GetDC()->GetScreenRTV()->GetRTVSize();
			auto rtv = RenderTarget::CreateRTV(name, *pDev, size[0], size[1], ShaderUT::ComvertTextureFormat(format));
			m_shaderResourceList.push_back(rtv);
			ResourceManager::RegisterResource<RenderTarget>(rtv, name);

		}
		//ElementName��Depth�̏ꍇ
		else if (elm->GetName() == _T("Depth")) {
			tstring name = elm->GetAttribute(_T("Name"))->GetStringValue();
			tstring format = elm->GetAttribute(_T("Format"))->GetStringValue();
			auto size = elm->GetAttribute(_T("Size"))->GetInt2Value();

			if (size[0] < 0)
				size = pDev->GetDC()->GetScreenRTV()->GetRTVSize();
			auto dsv = DepthStencil::CreateDSV(name, *pDev, size[0], size[1], ShaderUT::ComvertTextureFormat(format));
			m_shaderResourceList.push_back(dsv);
			ResourceManager::RegisterResource<DepthStencil>(dsv, name);

		}
		elm = elm->Next();
	}
	return true;
}
