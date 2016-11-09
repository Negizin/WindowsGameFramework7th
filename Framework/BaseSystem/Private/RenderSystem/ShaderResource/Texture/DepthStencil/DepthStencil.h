//!*******************************************************
//!	DepyhStencil.h
//!
//!	
//!
#pragma once
#include	"../Texture.h"
#include	"../../../Utilities/Interface/IStaticNameObjectList.h"

class DX11Device;
class DepthStencil :public Texture2D, IStaticNameObjectList<DepthStencil>
{
public:
	DepthStencil() :m_depthStencil(nullptr){};
	virtual ~DepthStencil();
	static DepthStencil* CreateDSV(
		tstring name,
		DX11Device& dev,
		UINT width,
		UINT height,
		DXGI_FORMAT format = DXGI_FORMAT_D24_UNORM_S8_UINT);

	ID3D11DepthStencilState* GetDSS()const{ return m_depthStencil; }
	ID3D11DepthStencilView * GetDSV()const{ return m_depthStencilView; }
private:
	bool Create( DX11Device& dev,
		UINT width,
		UINT height,
		DXGI_FORMAT format);

	ID3D11DepthStencilState* m_depthStencil;
	ID3D11DepthStencilView * m_depthStencilView;
};