/*!-----------------------------------------------------------------/
//@brief	Texture.h
//
//  テクスチャラッピング
//
//@Auther   宮原敏史
//@Date     2016/10/22
//-----------------------------------------------------------------*/
#pragma once
#include <d3d11.h>
#include	"../ShaderResouce.h"
#include	"../../Utilities/NameObject/NameObject.h"


//	Texture
class Texture : public ShaderResource,
	public NameObject {
public:
	Texture() :m_srv(nullptr) {};
	virtual ~Texture() {
		SafeRelease(m_srv);
	}


	ID3D11ShaderResourceView * GetSRV()const { return m_srv; }

	bool SetSRV(ID3D11ShaderResourceView*srv) {
		if (m_srv)
			return FALSE;
		m_srv = srv;
		return TRUE;
	}
protected:
	ID3D11ShaderResourceView * m_srv;
	int m_registerIndex = 0;
};


//	Texture2D
class Texture2D : public Texture {
public:
	Texture2D() :m_tex2d(nullptr) {};
	virtual ~Texture2D() {
		SafeRelease(m_tex2d);
	}

protected:
	ID3D11Texture2D * m_tex2d;
};
