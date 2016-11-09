//!*******************************************************
//!	VertexBuffer.h
//!
//!	vertex buffer.
//!

#pragma once
#include "Buffer.h"

class VertexBuffer : public Buffer {
public:
	VertexBuffer();
	bool SetStride(UINT stride);
	bool SetOffset(UINT offset);
	UINT GetStride()const;
	UINT GetOffset()const;

	bool CreateVertexBuffer(
		__in DX11Device *dev,
		__in void * pData,
		__in size_t size,
		size_t stride,
		UINT offset);

private:
	UINT m_stride;
	UINT m_offset;
};