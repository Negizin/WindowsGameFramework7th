#include	"MeshFactory.h"
#include	"MeshObject.h"
#include	"../Utilities/Lodaer/PmxLoader.h"
#include	"../Buffer/VertexBuffer.h"
#include	"../ResourceManager/ResourceManager.h"
#include	"../RenderSystem.h"

MeshFactory::MeshFactory() {

}

MeshFactory::~MeshFactory() {

}

bool MeshFactory::LoadModelFromFile(DX11Device *pDev, tstring filename, tstring name) {
	MeshObject *pMesh = new MeshObject;
	pMesh->SetName(name);

	if (filename.rfind(_T(".pmx")) != tstring::npos) {
		PmxLoader loader;
		if (!loader.LoadFromFile(filename)) {
			return false;
		}


		VertexBuffer *vb = new VertexBuffer();
		vb->CreateVertexBuffer(pDev,
			loader.GetVertexBuffer(0),
			loader.GetVertexSize(0),
			loader.GetVertexStride(),
			0);
		IndexBuffer *ib = new IndexBuffer();
		ib->CreateIndexBuffer(pDev,
			loader.GetIndexBuffer(0),
			loader.GetIndexBufferSize(0));

		Mesh *mesh = new Mesh;
		mesh->m_vertexBuffer = vb;
		mesh->m_indexBuffer = ib;



		GeometryObject *obj = nullptr;
		SkinMeshObject *skin = new SkinMeshObject();
		skin->CreateGeometryObject(pDev, nullptr, nullptr);
		skin->SetMesh(mesh);

		for (unsigned int i = 0; i < loader.GetMaterialNum(); ++i) {
			PmxMaterialBase *mat = new PmxMaterialBase();

			mat->SetDiffuse(loader.GetMaterial(i)->m_material.diffuse);
			mat->SetEmissive(loader.GetMaterial(i)->m_material.emissive);
			mat->SetSpecular(loader.GetMaterial(i)->m_material.specular);
			mat->m_textureName = loader.GetMaterial(i)->m_textureName;
			mat->materialMeshCnt = loader.GetMaterial(i)->materialMeshCnt;
			Texture2D *tex = ResourceManager::Find<Texture2D>(mat->m_textureName);
			if (tex == nullptr) {
				mat->LoadTextureFromFile(pDev);
				tex = mat->GetTexture();
				ResourceManager::RegisterResource<Texture2D>(tex, mat->m_textureName);
			}

			skin->SetMaterial(mat);
		}


		obj = skin;

		pMesh->AddGeometry(skin);

		ResourceManager::RegisterResource<MeshObject>(pMesh, name);
		return true;
	}
}

/*! =====================================================================================
@brief	モデルファイル読み込み
@param	void
@return void
====================================================================================== */
bool MeshFactory::LoadModelFromFile(tstring filename, tstring name) {
	return LoadModelFromFile(RenderSystem::GetDevice(), filename, name);
}
