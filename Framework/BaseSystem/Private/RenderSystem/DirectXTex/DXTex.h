//!*******************************************************
//!	DXTex.h
//!
//!	Create Texture From File.
//!

#pragma once
#include <d3d11.h>
class DXTex {
public:
	static ID3D11ShaderResourceView * LoadFromFile(ID3D11Device * pDev, const TCHAR* fileName);
};