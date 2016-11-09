#include "DX11Device.h"
#include "../../UT/Helper.h"
#include "../ResouceDesc/ResouceDesc.h"
#include "../DeviceContext/DeviceContext.h"
#include "../RenderTarget/RenderTarget.h"
#include "../DepthStencil/DepthStencil.h"
#include "../State/SamplerState.h"
#include "../ViewPort/ViewPort.h"
#include <DXGI.h>

#pragma comment(lib,"DXGI.lib")

bool DX11Device::GetRefreshRato(UINT refreshRatox, UINT refreshRatoy, const UINT width, const UINT height){
	refreshRatox = 1;
	refreshRatoy = 60;
	//変数
	HRESULT	hr = S_OK;
	IDXGIFactory* factory;				// factory
	IDXGIAdapter* adapter;				// videocard
	IDXGIOutput* adapterOutput;			// monitor
	UINT numModes;
	DXGI_MODE_DESC* displayModeList;

	// Create a DirectX graphics interface factory
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(hr)){ return FALSE; }

	// use the factory to create an adpter for the primary graphics interface(video card)
	hr = factory->EnumAdapters(0, &adapter);
	if (FAILED(hr)){ return FALSE; }

	// enumerrate primary adapter output(monitor)
	hr = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(hr)){ return FALSE; }

	// get the number of modes that fit the DXGI_FORMAT_R8G8B8_UNORM display format forthe adapter output(monitor)
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(hr)){ return FALSE; }

	// create alist to hold all possible display modes for this monitor/video card combination
	displayModeList = new(DXGI_MODE_DESC[numModes]);
	if (!displayModeList){ return FALSE; }

	// now fill the display mode list structures
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(hr)){ return FALSE; }

	// now go through all the display modes and find the one that matches the screen width and height
	// when a match is found store the numerator and denominator of the refresh rate for that monitor
	for (UINT i = 0; i < numModes; i++){
		if (displayModeList[i].Width == width){
			if (displayModeList[i].Height == height){
				refreshRatox = displayModeList[i].RefreshRate.Numerator;
				refreshRatoy = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	SafeDeleteArray(displayModeList);
	SafeRelease(adapterOutput);
	SafeRelease(adapter);
	SafeRelease(factory);

	return TRUE;
}

DeviceContext* DX11Device::GetDC()const
{
	return m_deviceContext;
}

bool DX11Device::CreateDevice(HWND hWnd, int width, int height){
	//===================================
	//! Step1 
	//	Setting SwapChain
	//===================================

	//リフレッシュレートの取得
	int refreshRatoX=0, refreshRatoY=0;
	bool result = GetRefreshRato(refreshRatoX, refreshRatoY, width, height);
	if (result == FALSE) return result;

	SWAP_CHAIN_DESC swapChainDesc(hWnd, width, height, refreshRatoX, refreshRatoY);

	//===================================
	//! Step2 
	//	Create Device & Context & SwapChain
	//===================================

	// ドライバの種類の列挙
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	// 機能レベルの列挙
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3, D3D_FEATURE_LEVEL_9_2, D3D_FEATURE_LEVEL_9_1
	};

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

#ifdef _DEBUG
	//UINT devCreateFlag = D3D11_CREATE_DEVICE_DEBUG;
	UINT devCreateFlag = 0;
#else
	UINT devCreateFlag = 0;
#endif

	ID3D11DeviceContext * pDevContext;

	HRESULT hr;
	for (UINT i = 0; i < numDriverTypes; ++i)
	{
		m_driverType = driverTypes[i];
		hr = D3D11CreateDeviceAndSwapChain(
			nullptr,			// ディスプレイデバイスのアダプタ（ＮＵＬＬの場合最初に見つかったアダプタ）
			m_driverType,		// デバイスドライバのタイプ
			nullptr,			// ソフトウェアラスタライザを使用する場合に指定する
			devCreateFlag,		// デバイスの生成フラグ
			featureLevels,		// 機能レベル
			numFeatureLevels,	// 機能レベル数
			D3D11_SDK_VERSION,	// Dx11 バージョン
			&swapChainDesc,	// スワップチェインの設定
			&m_swapChain,		// IDXGIDwapChainインタフェース	
			&m_device,			// ID3D11Deviceインタフェース
			&m_featureLevel,	// サポートされている機能レベル
			&pDevContext);		// デバイスコンテキスト
		if (SUCCEEDED(hr))break;
	}
	if (FAILED(hr)){ return FALSE; }

	//! Create Context 
	m_deviceContext = new DeviceContext(this, pDevContext);
	RenderTarget* rtv = RenderTarget::CrateScreenRTV(*this);
	m_deviceContext->SetScreenRTV(rtv);
	
	DepthStencil* depthStencil =
		DepthStencil::CreateDSV("MainDepthStencil",*this, width, height);
	m_deviceContext->SetMainDepthStencil(depthStencil);
	
	m_deviceContext->ResetDrawCallCount();
	m_deviceContext->SetRT(0, rtv);
	//m_deviceContext->ApplyRenderTargets();
	
	Viewport viewport;
	viewport.Create(width, height);
	m_deviceContext->SetViewport(&viewport);
	
	CreateAndSetRaster();
//	CreateDeffardContext();
	
	LoadDefaultShader();

	return TRUE;
}


bool DX11Device::CreateAndSetRaster()
{
	HRESULT hr;
	D3D11_RASTERIZER_DESC rasterDesc;
	ID3D11RasterizerState* rasterState;

	// setup the raster description which will determine how and what polygons will be drawn
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = FALSE;
	rasterDesc.MultisampleEnable = FALSE;
	rasterDesc.ScissorEnable = FALSE;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// create the rasterrizer state from the description we just filled out 
	hr = m_device->CreateRasterizerState(&rasterDesc, &rasterState);
	if (FAILED(hr))
	{
		return FALSE;
	}


	return TRUE;
}

SamplerState*  DX11Device::CreateSamplerState(const D3D11_SAMPLER_DESC& desc){

	ID3D11SamplerState * pSampler;
	m_device->CreateSamplerState(&desc, &pSampler);
	if (pSampler)
	{
		SamplerState * m_pSampler = new SamplerState;
		m_pSampler->SetD3DSamplerState(pSampler);
		return m_pSampler;
	}
	return nullptr;
}

bool DX11Device::LoadDefaultShader()
{
	return TRUE;
}

bool DX11Device::Flip()
{
	if (m_device && m_swapChain)
		m_swapChain->Present(0, 0);
	else
		return FALSE;
	return TRUE;
}

bool DX11Device::CreateDeffardContext()
{
	HRESULT hr;
	ID3D11DeviceContext * pDevContext;
	for (int i = 0; i < MAX_DDC; i++){
		hr = m_device->CreateDeferredContext(0, &pDevContext);
		m_DefferadContext[i] = new DeviceContext(this, pDevContext);
	}
	return TRUE;
}

void DX11Device::Release(){
	SafeRelease(m_device);
	SafeRelease(m_swapChain);
	SafeDelete(m_deviceContext);
	//SafeDeleteArray(m_DefferadContext[0]);
}