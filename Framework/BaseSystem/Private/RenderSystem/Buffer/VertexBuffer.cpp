#include "VertexBuffer.h"
/*!-----------------------------------------------------------------/
//@brief	VertexBuffer()
//
//  �R���X�g���N�^
//
//@Param[in]	void
//@Param[out]	void
//@Auther   �{���q�j
//@Date		2016/10/22
//-----------------------------------------------------------------*/
VertexBuffer::VertexBuffer()
	:m_offset(0), m_stride(0) {

}

bool VertexBuffer::SetStride(UINT stride) {
	m_stride = stride;
	return TRUE;
}
bool VertexBuffer::SetOffset(UINT offset) {
	m_offset = offset;
	return TRUE;
}
UINT VertexBuffer::GetStride()const {
	return m_stride;
}
UINT VertexBuffer::GetOffset()const {
	return m_offset;
}

/*!-----------------------------------------------------------------/
//@brief	CreateVertexBuffer
//
//  VertexBuffer�̍쐬
//
//@Param[in]	DX11Device *dev
//@Param[in]	void * pData
//@Param[in]	size_t size
//@Param[in]	size_t stride
//@Param[in]	UINT �@offset
//@Param[out]	bool   hr
//@Auther   �{���q�j
//@Date		2016/10/22
//-----------------------------------------------------------------*/
bool VertexBuffer::CreateVertexBuffer(__in DX11Device *dev,
	__in void * pData,
	__in size_t size,
	size_t stride,
	UINT offset) {
	bool hr = CreateBuffer(dev, pData, size, 0,
		D3D11_BIND_VERTEX_BUFFER);
	SetBufferSize(size);
	SetStride(stride);
	SetOffset(offset);
	return hr;
}