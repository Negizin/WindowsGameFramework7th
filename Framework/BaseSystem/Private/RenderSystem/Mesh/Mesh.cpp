#include "Mesh.h"

Mesh::Mesh() :
	m_vertexBuffer(nullptr),
	m_indexBuffer(nullptr) {
}

Mesh::~Mesh() {
	SafeDelete(m_vertexBuffer);
	SafeDelete(m_indexBuffer);
}

//todo
bool Mesh::CreateVertexBuffer(DX11Device * pDev, void * memory, size_t sz) {
	(void) pDev;
	(void) memory;
	(void) sz;
	return FALSE;
}

//todo
bool Mesh::CreateIndexBuffer(DX11Device * pDev, void * memory, size_t sz) {
	(void) pDev;
	(void) memory;
	(void) sz;
	return FALSE;
}

int Mesh::GetVertexNum() {
	int sz = m_vertexBuffer->GetBufferSize() / m_vertexBuffer->GetStride();
	return sz;
}

VertexBuffer* Mesh::GetVertexBuffer()const {
	return m_vertexBuffer;
}
IndexBuffer* Mesh::GetIndexBuffer()const {
	return m_indexBuffer;
}