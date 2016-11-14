#include "DepthStencil.h"


DepthStencil::~DepthStencil(){
	SafeRelease(m_depthStencil);
}

// Static List ‚Ìì¬
INSTANTIATE_NAME_OBJ_LIST(DepthStencil)

//! Depth Stencil ‚Ìì¬
bool DepthStencil::Create(DX11Device& dev,
	UINT width,
	UINT height,
	DXGI_FORMAT format /*= DXGI_FORMAT_D24_UNORM_S8_UINT */)
{
	ID3D11Device* pDev = dev.GetDevD3D();

	// step 1 create depth texture
	{
		TEX2D_DESC desc(width, height, format, D3D11_BIND_DEPTH_STENCIL);
		HRESULT hr = pDev->CreateTexture2D(&desc, nullptr, &m_tex2d);
		//DEPTH_STENCIL_CREATE_ERR_TO_RETURN;
	}

	
	// step 3 create view
	{	//todo 
		D3D11_DEPTH_STENCIL_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipSlice = 0;

		HRESULT hr = pDev->CreateDepthStencilView(m_tex2d, &desc, &m_depthStencilView);
	}
	return TRUE;
}

// Depth Stencil View‚Ì ì¬
DepthStencil* DepthStencil::CreateDSV(
	tstring name,
	 DX11Device& dev,
	UINT width,
	UINT height,
	DXGI_FORMAT format /*= DXGI_FORMAT_D24_UNORM_S8_UINT */)
{
	DepthStencil * dsv = new DepthStencil();
	auto success = dsv->Create(dev, width, height, format);

	if (!success)
	{
		SafeDelete(dsv);
		return dsv;
	}
	dsv->SetName(name);
	//AddObject(dsv);

	return dsv;
}