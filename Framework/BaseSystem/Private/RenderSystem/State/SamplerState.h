/*!-----------------------------------------------------------------/
//@brief	SamplerState.h
//
//  サンプラーステートクラス
//
//@Auther   宮原敏史
//@Date     2016/10/30
//-----------------------------------------------------------------*/
#pragma once

#include <d3d11.h>
#include	"../../../Public/Common/Common.h"
#include	"../Utilities/NameObject/NameObject.h"

class SamplerState:public NameObject
{
public:
	SamplerState(const tstring& name = _T("Sampler"));
	~SamplerState();
	ID3D11SamplerState *GetSamplerState()const;
	bool SetD3DSamplerState(ID3D11SamplerState *pD3DSampler);
private:
	ID3D11SamplerState *m_pD3DSampler;
};

