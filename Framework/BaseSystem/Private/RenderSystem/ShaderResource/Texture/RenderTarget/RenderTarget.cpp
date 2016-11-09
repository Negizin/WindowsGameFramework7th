#include "RenderTarget.h"

RenderTarget::RenderTarget() :m_rtv(nullptr) {};

RenderTarget::~RenderTarget() {
	UnInit();
}


// Static List の作成
INSTANTIATE_NAME_OBJ_LIST(RenderTarget)


std::array<int, 2> RenderTarget::GetRTVSize()const {
	return m_rtvSize;
}
void RenderTarget::UnInit() {
	SafeRelease(m_rtv);
	SafeRelease(m_srv);
	SafeRelease(m_tex2d);
}

bool RenderTarget::Create(DX11Device& dev,
	const int width,
	const int height,
	DXGI_FORMAT format /*= DXGI_FORMAT_R8G8B8A8_UNORM*/) {
	UnInit();

	ID3D11Device* pDev = dev.GetDevD3D();

	// Step 1 Create Texture
	{
		TEX2D_DESC texDesc(width, height, format);

		HRESULT hr = pDev->CreateTexture2D(&texDesc, nullptr, &m_tex2d);
		//RTV_CREATE_ERR_TO_RETURN;
	}

	// Step 2 Create Render Target View
	{
		RTV_DESC desc(format);

		HRESULT hr = pDev->CreateRenderTargetView(m_tex2d, &desc, &m_rtv);
		//RTV_CREATE_ERR_TO_RETURN;
	}

	// Step 3 Create Shader Resource View
	{
		SRV_DESC desc(format);

		HRESULT hr = pDev->CreateShaderResourceView(m_tex2d, &desc, &m_srv);
		//RTV_CREATE_ERR_TO_RETURN;
	}

	// Step 4 Create Sample State 
	// *RenderTarget ごとにサンプラを持つ必要はない。

	return TRUE;
}

RenderTarget* RenderTarget::CrateScreenRTV(DX11Device& dev) {
	ID3D11Device * pDev = dev.GetDevD3D();
	IDXGISwapChain * pSC = dev.GetSC();

	// Swap Chain から　バックバッファへのポインタを取得
	ID3D11Texture2D* pBackBuffer = NULL;
	ID3D11RenderTargetView* pD3Drtv;
	HRESULT hr = pSC->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*) &pBackBuffer);
	//RTV_CREATE_ERR_TO_RETURN;

	// バックバッファへのポインタを指定してRTVを作成
	hr = pDev->CreateRenderTargetView(pBackBuffer, NULL, &pD3Drtv);
	SafeRelease(pBackBuffer);

	//RTV_CREATE_ERR_TO_RETURN;
	RenderTarget* rtv = new RenderTarget();
	rtv->SetName(_T("ScreenRenderTargetView"));
	rtv->m_rtv = pD3Drtv;
	//AddObject(rtv);

	return rtv;
}

RenderTarget* RenderTarget::CreateRTV(
	tstring name,
	DX11Device& dev,
	const int width,
	const int height,
	DXGI_FORMAT format/* = DXGI_FORMAT_R8G8B8A8_UNORM */) {
	RenderTarget * rtv = new RenderTarget();
	bool succed = rtv->Create(dev, width, height, format);

	if (!succed) {
		SafeDelete(rtv);
		return nullptr;
	}
	rtv->SetName(name);
	//AddObject(rtv);
	return rtv;
}


