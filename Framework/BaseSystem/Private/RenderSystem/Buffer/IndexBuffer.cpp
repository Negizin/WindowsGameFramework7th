#include "IndexBuffer.h"

IndexBuffer::IndexBuffer() {

}

bool IndexBuffer::CreateIndexBuffer(
	__in DX11Device *dev,
	__in void * pData,
	__in size_t size) {

	bool hr = CreateBuffer(dev, pData, size, 0, D3D11_BIND_INDEX_BUFFER);
	SetBufferSize(size);
	return hr;
}