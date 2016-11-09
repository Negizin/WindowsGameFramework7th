#pragma once
#include "../DX11Include/DX11IncludeHeader.h"

//dx11 multi sample desc.
struct SAMPLE_DESC : DXGI_SAMPLE_DESC
{
	SAMPLE_DESC(int count = 1, int quality = 0)
	{
		Count = (int)count;
		Quality = (int)quality;
	}
};

struct MODE_DESC : DXGI_MODE_DESC
{
	MODE_DESC(UINT width,
		UINT height,
		int refreshRatoX,
		int refreshRatoY,
		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_MODE_SCANLINE_ORDER scanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
		DXGI_MODE_SCALING  scaling = DXGI_MODE_SCALING_UNSPECIFIED)
	{
		Width = width;							// バックバッファの幅
		Height = height;						// バックバッファの高さ
		Format = format;						// バックバッファフォーマット(R,G,B 範囲０．０から１．０)
		RefreshRate.Numerator = refreshRatoX;	// リフレッシュレート（分母）
		RefreshRate.Denominator = refreshRatoY; // リフレッシュレート（分子）
		ScanlineOrdering = scanlineOrdering;
		Scaling = scaling;
	}
};

// dx11 swapchain desc
struct SWAP_CHAIN_DESC : DXGI_SWAP_CHAIN_DESC
{
	//todo
	SWAP_CHAIN_DESC(HWND hWnd,
		UINT width,
		UINT height,
		int refreshRatoX,
		int refreshRatoY,
		bool isFullScreen = FALSE)
	{
		BufferCount = 1;											// バックバッファの数
		BufferDesc = MODE_DESC(width, height, refreshRatoX, refreshRatoY);
		BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;				// バックバッファの使用方法
		OutputWindow = hWnd;										// 関連付けるウインドウ
		SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		SampleDesc = SAMPLE_DESC();
		Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		Windowed = !isFullScreen;
	}
};
// dx11 sampler desc.
struct SAMPLER_DESC : D3D11_SAMPLER_DESC
{
	//todo
};

// dx11 buffer desc.
struct BUFFER_DESC : D3D11_BUFFER_DESC
{
	//todo
};

struct DEPTH_STENCIL_DESC : D3D11_DEPTH_STENCIL_DESC
{
	DEPTH_STENCIL_DESC()
	{
		ZeroMemory(this, sizeof(DEPTH_STENCIL_DESC));
		DepthEnable = TRUE;
		DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		DepthFunc = D3D11_COMPARISON_LESS;

		// set up the description of the stencl state
		StencilEnable = TRUE;
		StencilReadMask = 0xFF;
		StencilWriteMask = 0xFF;

		// stencil operation if pixel is front-facing
		FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		// stencil operation if pixel is　back-facing
		BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	}
};

struct SRV_DESC : D3D11_SHADER_RESOURCE_VIEW_DESC
{
	SRV_DESC(DXGI_FORMAT format)
	{
		ZeroMemory(this, sizeof(SRV_DESC));
		Format = format;
		ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	}
};

// dx11 rtv desc
struct RTV_DESC : D3D11_RENDER_TARGET_VIEW_DESC
{
	RTV_DESC(DXGI_FORMAT format)
	{
		Format = format;
		ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

		Buffer.FirstElement = 0;
		Buffer.ElementOffset = 0;

		Texture1D.MipSlice = 0;
		Texture2D.MipSlice = 0;
		Texture3D.MipSlice = 0;

		Texture2DMS.UnusedField_NothingToDefine = 0;

		Texture1DArray.ArraySize = 0;
		Texture1DArray.FirstArraySlice = 0;
		Texture1DArray.MipSlice = 0;

		Texture2DArray.ArraySize = 0;
		Texture2DArray.FirstArraySlice = 0;
		Texture2DArray.MipSlice = 0;

		Texture2DMSArray.ArraySize = 0;
		Texture2DMSArray.FirstArraySlice = 0;
	}
};

// dx11 texture desc.
struct TEX2D_DESC : D3D11_TEXTURE2D_DESC
{
	TEX2D_DESC(UINT width,
		UINT height,
		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM,
		D3D11_BIND_FLAG bindflg = D3D11_BIND_SHADER_RESOURCE,
		UINT cpuAccess = 0,
		D3D11_USAGE usage = D3D11_USAGE_DEFAULT,
		UINT mipmapLevel = 1,
		SAMPLE_DESC sample = SAMPLE_DESC(),
		UINT miscflg = 0,
		UINT arraySize = 1
		)
	{
		Width = width;
		Height = height;
		BindFlags = bindflg;
		Format = format;
		CPUAccessFlags = cpuAccess;
		Usage = usage;
		MipLevels = mipmapLevel;
		SampleDesc = sample;
		MiscFlags = miscflg;
		ArraySize = arraySize;
	}
};