/*!-----------------------------------------------------------------/
//@brief	ViewPort
//
//  ビューポートクラス
//
//@Auther   宮原敏史
//@Date     2016/10/22
//-----------------------------------------------------------------*/
#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

class Viewport {
public:
	void Create(const UINT width,
		const UINT height,
		const UINT _topLeftX = 0,
		const UINT _topLeftY = 0,
		const FLOAT _minDpeth = 0.0f,
		const FLOAT _maxDpeth = 1.0f);
	XMFLOAT2 GetSize();
	const D3D11_VIEWPORT* GetD3DViewport()const;
protected:
	D3D11_VIEWPORT	m_d3dviewport;
};