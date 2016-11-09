#include "CBuffer.h"

//! Constructor
CBuffer::CBuffer()
	:m_bindShaderType(SHADER_TYPE::UNKNOWN_SHADER) {

}

//! Destructor
CBuffer::~CBuffer() {

}

bool CBuffer::CreateCBuffer(
	__in DX11Device *dev,
	__in void * pData,
	__in size_t size) {
	bool hr = CreateBuffer(dev, pData, size,
		D3D11_CPU_ACCESS_WRITE,
		D3D11_BIND_CONSTANT_BUFFER);

	SetBufferSize(size);

	return hr;
}