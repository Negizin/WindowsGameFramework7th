//!*******************************************************
//!	IndexBuffer.h
//!
//!	Index Buffer.
//!

#pragma once
#include	"Buffer.h"

class IndexBuffer : public Buffer {
public:
	IndexBuffer();


	bool CreateIndexBuffer(
		__in DX11Device *dev,
		__in void * pData,
		__in size_t size);
private:
};