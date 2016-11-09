//!*******************************************************
//!	RenderTaeget.h
//!
//!	
//! RenderTarget		BaseClass Texture

#pragma once
#include	"../Texture.h"
#include	"../../../Utilities/Interface/IStaticNameObjectList.h"
#include	<array>


class DX11Device;
class RenderTarget :public Texture2D, IStaticNameObjectList<RenderTarget> {
public:
	virtual ~RenderTarget();

	ID3D11RenderTargetView* GetRTV() {
		return m_rtv;
	}

	std::array<int, 2> GetRTVSize()const;

	static RenderTarget* CrateScreenRTV(DX11Device& dev);
	static RenderTarget* CreateRTV(
		tstring name,
		DX11Device& dev,
		const int width,
		const int height,
		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
protected:
	void operator = (RenderTarget*) = delete;
	RenderTarget(const RenderTarget&) = delete;
	RenderTarget();

	bool Create(DX11Device& dev,
		const int width,
		const int height,
		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
	void UnInit();

private:
	ID3D11RenderTargetView*	  m_rtv;
	std::array<int, 2>					  m_rtvSize;
};