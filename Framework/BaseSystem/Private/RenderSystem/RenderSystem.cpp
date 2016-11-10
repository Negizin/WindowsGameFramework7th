#include	"RenderSystem.h"
#include	"ShaderResource\Texture\Texture.h"
#include	"DirectXTex\DXTex.h"
#include	"ShaderResource\Texture\RenderTarget\RenderTarget.h"
#include	"ShaderResource\Texture\DepthStencil\DepthStencil.h"
#include	"ResourceManager\ResourceManager.h"

#include	"../../Public/MainWindow/MainWindow.h"

DX11Device*	RenderSystem::m_pDevice = nullptr;

/*! =====================================================================================
@brief	コンストラクタ
====================================================================================== */
RenderSystem::RenderSystem() {

}

/*! =====================================================================================
@brief	デストラクタ
====================================================================================== */
RenderSystem::~RenderSystem() {
	SafeDelete(m_pDevice);
}

/*! =====================================================================================
@brief	初期化処理（デバイス生成）
@param	HWND：ウィンドウハンドル
@return	bool
====================================================================================== */
bool	RenderSystem::Initialize(HWND _hWnd) {
	m_pDevice = new DX11Device();
	bool _bResult = m_pDevice->CreateDevice(_hWnd, MainWindow::GetWindowWidth(), MainWindow::GetWindowHeight());
	if (_bResult == false) {
		MessageBox(NULL, _T("Initialize() is fail"), _T("Error:RenderSystem.cpp"), MB_OK);
		return false;
	}
	return true;
}

/*! =====================================================================================
@brief	描画要求受付前処理（描画用キュー,RTV,DSVなどのバッファクリア）
@param	void
@return HRESULT (互換性のため、常にS_OKを返す）
====================================================================================== */
HRESULT	RenderSystem::StartReceivingDrawObject() {
	m_pDevice->GetDC()->Clear();	//RTV・DSVクリア
	return S_OK;
}

/*! =====================================================================================
@brief	描画キュー処理
@param	void
@return bool
====================================================================================== */
bool RenderSystem::Render() {

	m_PreFlowAndQue.Render(m_pDevice->GetDC());
	m_FlowAndQue.Render(m_pDevice->GetDC());
	m_PostFlowAndQue.Render(m_pDevice->GetDC());

	m_pDevice->Flip();
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

/*! =====================================================================================
@brief	デバイス取得
@param	void
@return void
====================================================================================== */
const DX11Device * RenderSystem::GetDevice() {
	return m_pDevice;
}




bool RenderSystem::LoadRenderSystemFromXML(DX11Device* pDev, const tstring&name) {
	XML xml;
	xml.LoadXML(UT::Resource::GetRenderSystemDirectory() + name);
	auto elm = xml.GetRootNode()->GetFirstChild();
	while (elm != nullptr) {
		//ElementNameがResourceの場合
		if (elm->GetName() == _T("Resource")) {
			tstring path = elm->GetAttribute(_T("resource"))->GetStringValue();
			UT::FilePathAnalyzer analyze(path);
			if (analyze.GetExtension() == _T(".shaderResource")) {
				LoadShaderResourceFromXML(pDev, path);
			}
		}
		//ElementNameがPreRenderの場合
		else if (elm->GetName() == _T("PreRender")) {
			tstring path = elm->GetAttribute(_T("flow"))->GetStringValue();
			UT::FilePathAnalyzer analyze(path);
			if (analyze.GetExtension() == _T(".shaderflow")) {
				RenderFlow *flow = new RenderFlow();
				flow->LoadFlomXML(pDev, path);
				m_PreFlowAndQue.m_pFlow = flow;
			}
		}
		//ElementNameがRenderの場合
		else if (elm->GetName() == _T("Render")) {
			tstring path = elm->GetAttribute(_T("flow"))->GetStringValue();
			UT::FilePathAnalyzer analyze(path);
			if (analyze.GetExtension() == _T(".shaderflow")) {
				RenderFlow *flow = new RenderFlow();
				flow->LoadFlomXML(pDev, path);
				m_FlowAndQue.m_pFlow = flow;
			}
		}
		//ElementNameがPostRenderの場合
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
		//ElementNameがTextureの場合
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
		//ElementNameがRenderTargetの場合
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
		//ElementNameがDepthの場合
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
