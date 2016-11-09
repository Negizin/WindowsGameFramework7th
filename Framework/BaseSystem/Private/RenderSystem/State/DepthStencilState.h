/*!-----------------------------------------------------------------/
//@brief	DepthStencilState.h
//
//  DepthStencilStateLapperClass
//
//@Auther   ã{å¥ïqéj
//@Date     2016/10/31
//-----------------------------------------------------------------*/
#pragma once
#include	<d3d11.h>
#include	"../../../Public/Common/Common.h"

enum COMPARISON_FUNC {
	NEVER = 1,			//&0 èÌÇ…ïsçáäi
	LESS = 2,			//<= É\Å[ÉXÇ™ëŒè€ÇÊÇËè¨Ç≥Ç¢Ç∆Ç´Ç…çáäi
	EQUAL = 3,			//== ìôÇµÇ¢éûÇ…çáäi
	LESS_EQUAL = 4,		//<=  è¨Ç≥Ç¢Ç©ìôÇµÇ¢éûÇ…çáäi
	GREATER = 5,		//>  É\Å[ÉXÇ™ëŒè€ÇÊÇËëÂÇ´Ç¢éûÇ…çáäi
	NOT_EQUAL = 6,		//!= ìôÇµÇ≠Ç»Ç¢Ç∆Ç´Ç…çáäi
	GREATER_EQUAL = 7,	//>= ëÂÇ´Ç¢Ç∆Ç´Ç©ìôÇµÇ¢éûÇ…çáäi
	ALWAYS = 8,			//|1 èÌÇ…çáäi
};


class DX11Device;
class DepthStencilState {
public:
	DepthStencilState();
	~DepthStencilState();
	bool CreateDepthStencilState(DX11Device * pDev);
	bool SetZEnable(bool flag);
	bool SetZWriteEnable(bool flag);
	bool SetDepthTestFunction(COMPARISON_FUNC fiunction);
	bool SetDepthTestFunctionByString(const tstring & name);

	ID3D11DepthStencilState *GetDSS() { return m_pDepthStencilState; }
private:
	ID3D11DepthStencilState *m_pDepthStencilState;
	bool m_ZWriteEnable;
	bool m_ZEnable;
	COMPARISON_FUNC m_depthTestFunction;

};

