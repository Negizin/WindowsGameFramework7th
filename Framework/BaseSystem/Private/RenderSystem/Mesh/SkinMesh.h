#pragma once
#include "Mesh.h"
#include	"../Utilities/Bone/MmdBone.h"

class MeshFactory;
class DX11Device;

class SkinMesh :virtual public Mesh {
	friend class MeshFactory;

public:
	SkinMesh();
	virtual ~SkinMesh();
	bool CreateVertexBuffer(DX11Device *, void * memory, size_t sz);
	bool CreateIndexBuffer(DX11Device *, void * memory, size_t sz);

	std::vector<MMDBone>& GetBone() { return bone; }
	std::vector<MMDIKBone>& GetIKBone() { return IKBone; }
private:
	std::vector<MMDBone> bone;
	std::vector<MMDIKBone> IKBone;
};

