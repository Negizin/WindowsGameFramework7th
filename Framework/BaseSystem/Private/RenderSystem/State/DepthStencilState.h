/*!-----------------------------------------------------------------/
//@brief	DepthStencilState.h
//
//  DepthStencilStateLapperClass
//
//@Auther   宮原敏史
//@Date     2016/10/31
//-----------------------------------------------------------------*/
#pragma once
#include	<d3d11.h>
#include	"../../../Public/Common/Common.h"

enum COMPARISON_FUNC {
	NEVER = 1,			//&0 常に不合格
	LESS = 2,			//<= ソースが対象より小さいときに合格
	EQUAL = 3,			//== 等しい時に合格
	LESS_EQUAL = 4,		//<=  小さいか等しい時に合格
	GREATER = 5,		//>  ソースが対象より大きい時に合格
	NOT_EQUAL = 6,		//!= 等しくないときに合格
	GREATER_EQUAL = 7,	//>= 大きいときか等しい時に合格
	ALWAYS = 8,			//|1 常に合格
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

