#include "ViewPort.h"

/*!-----------------------------------------------------------------/
//@brief	Create
//
//  �r���[�|�[�g�쐬
//
//@Param[in]	��
//@Param[in]	����
//@Param[in]	�����x���W
//@Param[in]	�����y���W
//@Param[in]	�ŏ��[�x
//@Param[in]	�ő�[�x
//@Param[out]	void
//@Auther   �{���q�j
//@Date		2016/10/22
//-----------------------------------------------------------------*/
void Viewport::Create(const UINT width,
	const UINT height,
	const UINT _topLeftX /*= 0   */,
	const UINT _topLeftY /*= 0   */,
	const FLOAT _minDpeth /*= 0.0f*/,
	const FLOAT _maxDpeth /*= 1.0f*/) {
	m_d3dviewport.Width = (FLOAT) width;
	m_d3dviewport.Height = (FLOAT) height;
	m_d3dviewport.TopLeftX = (FLOAT) _topLeftX;
	m_d3dviewport.TopLeftY = (FLOAT) _topLeftY;
	m_d3dviewport.MinDepth = _minDpeth;
	m_d3dviewport.MaxDepth = _maxDpeth;
}

/*!-----------------------------------------------------------------/
//@brief	GetSize
//
//  �T�C�Y�擾
//
//@Param[in]	void
//@Param[out]	���A����
//@Auther   �{���q�j
//@Date		2016/10/22
//-----------------------------------------------------------------*/
XMFLOAT2 Viewport::GetSize() {
	return XMFLOAT2((UINT) m_d3dviewport.Width, (UINT) m_d3dviewport.Height);
}

/*!-----------------------------------------------------------------/
//@brief	GetD3DViewport
//
//  �r���[�|�[�g�擾
//
//@Param[in]	void
//@Param[out]	�r���[�|�[�g
//@Auther   �{���q�j
//@Date		2016/10/22
//-----------------------------------------------------------------*/
const D3D11_VIEWPORT* Viewport::GetD3DViewport()const {
	return &m_d3dviewport;
}