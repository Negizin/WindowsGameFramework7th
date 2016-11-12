#include "SkinMesh.h"
#include "../Vertex/Vertex.h"

SkinMesh::SkinMesh() :Mesh() {
}

SkinMesh::~SkinMesh() {
}


bool SkinMesh::CreateVertexBuffer(DX11Device * pDev, void * memory, size_t sz) {
	m_vertexBuffer = new VertexBuffer;
	m_vertexBuffer->CreateVertexBuffer(pDev, memory, sizeof(VertexSkin)*sz, sizeof(VertexSkin), 0);
	return FALSE;
}

bool SkinMesh::CreateIndexBuffer(DX11Device * pDev, void * memory, size_t sz) {
	m_indexBuffer = new IndexBuffer;
	m_indexBuffer->CreateIndexBuffer(pDev, memory, sizeof(unsigned int)*sz);
	return FALSE;
}