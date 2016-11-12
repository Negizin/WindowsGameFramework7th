/*!-----------------------------------------------------------------/
//@brief	MeshLoader.h
//
//  ÉÅÉbÉVÉÖÉçÅ[É_Å[
//
//@Auther   ã{å¥ïqéj
//@Date     2016/11/08
//-----------------------------------------------------------------*/
#pragma once
#include "../BinaryUT/Binary.h"

class MeshLoader :public Binary {
public:
	MeshLoader() {};
	virtual ~MeshLoader() {};

	virtual bool LoadFromFile(const tstring& filename) = 0;
	virtual bool LoadFromMemory(void *memory, size_t size) = 0;
	virtual int GetMeshNum() = 0;
	virtual int GetVertexSize(int index) = 0;
	virtual void *GetVertexBuffer(int index) = 0;
	virtual size_t GetVertexStride() = 0;
	virtual size_t GetIndexBufferSize(int Index) { return 0; }
	virtual void *GetIndexBuffer(int index) { return nullptr; }

};