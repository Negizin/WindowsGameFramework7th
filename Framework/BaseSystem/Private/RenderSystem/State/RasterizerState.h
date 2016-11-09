/*!-----------------------------------------------------------------/
//@brief	RasterizerState.h
//
//  RasterizerStateLapperClass
//
//@Auther   ã{å¥ïqéj
//@Date     2016/10/31
//-----------------------------------------------------------------*/
#pragma once
#include	<d3d11.h>
#include	"../../../Public/Common/Common.h"

enum CULL_MODE {
	BACK = D3D11_CULL_BACK,
	FRONT = D3D11_CULL_FRONT,
	NONE = D3D11_CULL_NONE
};

enum FILL_MODE {
	SOLID = D3D11_FILL_MODE::D3D11_FILL_SOLID,
	WIREFRAME = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME
};


class DX11Device;
class RasterizerState {
public:
	RasterizerState();
	~RasterizerState();

	bool SetCullMode(CULL_MODE mode);
	bool SetFillMode(FILL_MODE mode);
	bool SetAnitiAliasMode(bool flg);

	bool SetCullModeByString(const tstring& name);
	bool SetFillModeByString(const tstring& name);

	bool CreateRasterizerState(DX11Device * pDev);
	bool operator ==(const RasterizerState& rasterizer);
	bool operator !=(const RasterizerState& rasterizer);

	ID3D11RasterizerState* GetRSS() { return m_pD3DrasterizerState; }
	CULL_MODE GetCullMode() { return m_cullMode; }
	FILL_MODE GetFillMode() { return m_fillMode; }
	bool	  GetAntiAliasMode() { return m_AntiAlias; }
private:
	CULL_MODE m_cullMode;
	FILL_MODE m_fillMode;
	bool	  m_AntiAlias;
	ID3D11RasterizerState *m_pD3DrasterizerState;
};

