#include	"RasterizerState.h"
#include	"../DX11Device/DX11Device.h"

RasterizerState::RasterizerState() {
}

RasterizerState::~RasterizerState() {
}


bool RasterizerState::SetCullMode(CULL_MODE mode) {
	m_cullMode = mode;
	return true;
}
bool RasterizerState::SetFillMode(FILL_MODE mode) {
	m_fillMode = mode;
	return true;
}
bool RasterizerState::SetAnitiAliasMode(bool flg) {
	m_AntiAlias = flg;
	return true;
}
bool RasterizerState::SetCullModeByString(const tstring& name) {
	if (name == _T("CCW"))
		m_cullMode = CULL_MODE::BACK;
	if (name == _T("CW"))
		m_cullMode = CULL_MODE::FRONT;
	if (name == _T("NONE"))
		m_cullMode = CULL_MODE::NONE;
	return true;
}
bool RasterizerState::SetFillModeByString(const tstring& name) {
	if (name == _T("SOLID"))
		m_fillMode = FILL_MODE::SOLID;
	if (name == _T("WIREFRAME"))
		m_fillMode = FILL_MODE::WIREFRAME;
	return true;
}
bool RasterizerState::CreateRasterizerState(DX11Device * pDev) {
	//SafeRelease(m_pD3DrasterizerState);
	HRESULT hr = S_FALSE;
	D3D11_RASTERIZER_DESC rasterDesc;

	// setup the raster description which will determine how and what polygons will be drawn
	rasterDesc.AntialiasedLineEnable = m_AntiAlias;
	rasterDesc.CullMode = (D3D11_CULL_MODE) m_cullMode;
	rasterDesc.FillMode = (D3D11_FILL_MODE) m_fillMode;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.SlopeScaledDepthBias = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;

	hr = pDev->GetDevD3D()->CreateRasterizerState(&rasterDesc, &m_pD3DrasterizerState);
	if (FAILED(hr)) {
		return false;
	}
	return true;
}
bool RasterizerState::operator ==(const RasterizerState& rasterizer) {

	bool b = m_cullMode == rasterizer.m_cullMode;
	b &= m_fillMode == rasterizer.m_fillMode;
	b &= m_AntiAlias == rasterizer.m_AntiAlias;
	return b;
}
bool RasterizerState::operator !=(const RasterizerState& rasterizer) {
	return !((*this) == rasterizer);
}