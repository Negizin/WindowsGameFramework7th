/*!-----------------------------------------------------------------/
//@brief	DX11Device.h
//
//  デバイスクラス、デバイスクラスインターフェイスの定義
//
//@Auther   宮原敏史
//@Date     2016/10/22
//-----------------------------------------------------------------*/
#pragma once
#include "../DX11Include/DX11IncludeHeader.h"
#include "DeviceContext.h"

class DeviceContext;
class SamplerState;

// Dx11 Device Intarface
class  IDX11Device {
public:
	//get device contetxt
	virtual DeviceContext*	GetDC()const = 0;
	virtual ID3D11Device*	GetDevD3D()const = 0;
	virtual IDXGISwapChain*	GetSC()const = 0;
private:

};


//Dx11	Device Class
class DX11Device :public IDX11Device {
public:
	DX11Device();
	~DX11Device();

	static const UINT	 MAX_DDC = 6;			//DeffardContextの最大数

	//=============================================
	// ! Get DeviceContext
	DeviceContext*	GetDC()const override;
	//=============================================
	// ! Get DirectX Device Pointer
	ID3D11Device*	GetDevD3D()const override;
	//=============================================
	// ! Get DirectX Swap Chain
	IDXGISwapChain*	GetSC()const override;

	//=============================================
	// ! CreateDevice
	// Create DirectX Device & SwapChain & DeviceContext
	// @pram hWnd	DirectXの描画ターゲットウィンドウハンドル
	//		 width & height Back Buffer Size
	// @return true is success
	bool CreateDevice(HWND hWnd, int width, int height);

	//=============================================
	// ! Release
	void Release();

	//=============================================
	// ! CreateSamplerState
	SamplerState*  CreateSamplerState(const D3D11_SAMPLER_DESC& desc);

	//=============================================
	// ! Flip
	// FlipScreen
	// @return true is success
	bool Flip();

private:

	//=============================================
	// ! GetRefreshRato
	// PC モニタのリフレッシュレートを取得
	// @pram _out refreshRato x = 分子　y =分母
	//		 上記の引数は戻り値として扱う。
	//		 width & height 画面サイズ
	// @return true is success
	bool GetRefreshRate(UINT* _pRefreshRatox, UINT *_pRefreshRatoy, const UINT width, const UINT height);

	//=============================================
	// ! LoadDefaultShader
	// デフォルトシェーダのロード
	// @return true is success
	bool LoadDefaultShader();

	//=============================================
	// ! CreateAndSetRaster
	// ラスタライザの作成と登録
	// @return true is success
	bool CreateAndSetRaster();

	//=============================================
	// ! CreateDeffardContext
	// ディファードコンテキストの作成
	// @return true is success
	bool CreateDeffardContext();
private:

	ID3D11Device*		m_device;
	IDXGISwapChain*		m_swapChain;
	D3D_DRIVER_TYPE		m_driverType;
	D3D_FEATURE_LEVEL	m_featureLevel;
	DeviceContext*		m_deviceContext;
	DeviceContext*		m_DefferadContext[MAX_DDC];
};

