#include "DepthStencilState.h"
#include	"../DX11Device/DX11Device.h"
#include	"../Utilities/ResourceDescription/ResouceDesc.h"


DepthStencilState::DepthStencilState()
	:m_depthTestFunction(COMPARISON_FUNC::LESS),
	m_ZEnable(true),
	m_ZWriteEnable(true),
	m_pDepthStencilState(nullptr) {
}

DepthStencilState::~DepthStencilState() {
}

bool DepthStencilState::CreateDepthStencilState(DX11Device* pDev) {
	DEPTH_STENCIL_DESC desc;
	desc.DepthWriteMask = (D3D11_DEPTH_WRITE_MASK) m_ZWriteEnable;
	desc.DepthEnable = m_ZWriteEnable;
	desc.DepthFunc = (D3D11_COMPARISON_FUNC) m_depthTestFunction;

	HRESULT hr = pDev->GetDevD3D()->CreateDepthStencilState(&desc, &m_pDepthStencilState);
	if (!SUCCEEDED(hr))
		return false;
	return true;
}

bool DepthStencilState::SetZEnable(bool flag) {
	m_ZEnable = flag;
	return true;
}
bool DepthStencilState::SetZWriteEnable(bool flag) {
	m_ZWriteEnable = flag;
	return true;
}
bool DepthStencilState::SetDepthTestFunction(COMPARISON_FUNC func) {
	m_depthTestFunction = func;
	return true;
}

bool DepthStencilState::SetDepthTestFunctionByString(const tstring& str) {
	if (str == _T("DNEVER"))
		m_depthTestFunction = COMPARISON_FUNC::NEVER;
	else if (str == _T("DLESS"))
		m_depthTestFunction = COMPARISON_FUNC::LESS;
	else if (str == _T("DEQUAL"))
		m_depthTestFunction = COMPARISON_FUNC::EQUAL;
	else if (str == _T("LESS_EQUAL"))
		m_depthTestFunction = COMPARISON_FUNC::LESS_EQUAL;
	else if (str == _T("GREATER"))
		m_depthTestFunction = COMPARISON_FUNC::GREATER;
	else if (str == _T("NOT_EQUAL"))
		m_depthTestFunction = COMPARISON_FUNC::NOT_EQUAL;
	else if (str == _T("GREATER_EQUAL"))
		m_depthTestFunction = COMPARISON_FUNC::GREATER_EQUAL;
	else if (str == _T("ALWAYS"))
		m_depthTestFunction = COMPARISON_FUNC::ALWAYS;

	return true;
}
