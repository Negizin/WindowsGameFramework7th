/*!-----------------------------------------------------------------/
//@brief	DepthStencilState.h
//
//  DepthStencilStateLapperClass
//
//@Auther   �{���q�j
//@Date     2016/10/31
//-----------------------------------------------------------------*/
#pragma once
#include	<d3d11.h>
#include	"../../../Public/Common/Common.h"

enum COMPARISON_FUNC {
	NEVER = 1,			//&0 ��ɕs���i
	LESS = 2,			//<= �\�[�X���Ώۂ�菬�����Ƃ��ɍ��i
	EQUAL = 3,			//== ���������ɍ��i
	LESS_EQUAL = 4,		//<=  �����������������ɍ��i
	GREATER = 5,		//>  �\�[�X���Ώۂ��傫�����ɍ��i
	NOT_EQUAL = 6,		//!= �������Ȃ��Ƃ��ɍ��i
	GREATER_EQUAL = 7,	//>= �傫���Ƃ������������ɍ��i
	ALWAYS = 8,			//|1 ��ɍ��i
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

