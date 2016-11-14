#include "SamplerState.h"

SamplerState::SamplerState(const tstring& name) {
	SetName(name);
}

SamplerState::~SamplerState() {
	
}

ID3D11SamplerState* SamplerState::GetSamplerState()const {
	return m_pD3DSampler;
}
bool SamplerState::SetD3DSamplerState(ID3D11SamplerState* pD3DSampler) {
	m_pD3DSampler = pD3DSampler;
	return true;
}