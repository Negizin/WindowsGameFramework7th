#pragma once
#include "../Buffer/VertexBuffer.h"
#include "../Buffer/IndexBuffer.h"
class MeshFactory;
class DX11Device;


class Mesh {
	friend class MeshFactory;

public:
	Mesh();
	virtual ~Mesh();
	virtual bool CreateVertexBuffer(DX11Device *, void * memory, size_t sz);
	virtual bool CreateIndexBuffer(DX11Device *, void * memory, size_t sz);
	int  GetVertexNum();
	VertexBuffer* GetVertexBuffer()const;
	IndexBuffer* GetIndexBuffer()const;
protected:
	VertexBuffer*	m_vertexBuffer;
	IndexBuffer*	m_indexBuffer;
};

