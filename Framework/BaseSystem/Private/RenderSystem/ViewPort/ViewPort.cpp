#include "ViewPort.h"

/*!-----------------------------------------------------------------/
//@brief	Create
//
//  ビューポート作成
//
//@Param[in]	幅
//@Param[in]	高さ
//@Param[in]	左上のx座標
//@Param[in]	左上のy座標
//@Param[in]	最小深度
//@Param[in]	最大深度
//@Param[out]	void
//@Auther   宮原敏史
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
//  サイズ取得
//
//@Param[in]	void
//@Param[out]	幅、高さ
//@Auther   宮原敏史
//@Date		2016/10/22
//-----------------------------------------------------------------*/
XMFLOAT2 Viewport::GetSize() {
	return XMFLOAT2((UINT) m_d3dviewport.Width, (UINT) m_d3dviewport.Height);
}

/*!-----------------------------------------------------------------/
//@brief	GetD3DViewport
//
//  ビューポート取得
//
//@Param[in]	void
//@Param[out]	ビューポート
//@Auther   宮原敏史
//@Date		2016/10/22
//-----------------------------------------------------------------*/
const D3D11_VIEWPORT* Viewport::GetD3DViewport()const {
	return &m_d3dviewport;
}