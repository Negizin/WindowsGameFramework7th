#include	"PmxLoader.h"
#include	"../../../../Public/Common/Common.h"

#include	"../../Material/MaterialBase.h"

#include    "../../DrawObject/skinmeshobject.h"
#include	<locale.h>
#include	<fstream>
#include	<stdio.h>
#include	 <tchar.h>

#pragma warning (disable:4996)

const TCHAR *	MODEL_FOLDER_PATH_PMX = _T("Resource/Model/");

template	<class T>
inline  void	SetLoadData(T* outData, unsigned	int	size, unsigned	char**	buffer) {

	memcpy(outData, *buffer, size);
	*buffer += size;

}

template<class T, int N>
inline void	SetLoadDataArry(T(&outData)[N], unsigned	int	size, unsigned int num, unsigned	char**	buffer) {
	for (unsigned int i = 0; i < num; i++) {
		memcpy(&outData[i], *buffer, size);
		*buffer += size;

	}
}


//
//inline std::wstring StringToWString(std::string oString) {
//	// SJIS → wstring
//	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str()
//		, -1, (wchar_t*) NULL, 0);
//
//	// バッファの取得
//	wchar_t* cpUCS2 = new wchar_t[iBufferSize];
//
//	// SJIS → wstring
//	MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2
//		, iBufferSize);
//
//	// stringの生成
//	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);
//
//	// バッファの破棄
//	delete[] cpUCS2;
//
//	// 変換結果を返す
//	return(oRet);
//}

//inline std::string WStringToString(std::wstring oWString) {
//	// wstring → SJIS
//	int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str()
//		, -1, (char *) NULL, 0, NULL, NULL);
//
//	// バッファの取得
//	CHAR* cpMultiByte = new CHAR[iBufferSize];
//
//	// wstring → SJIS
//	WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte
//		, iBufferSize, NULL, NULL);
//
//	// stringの生成
//	std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);
//
//	// バッファの破棄
//	delete[] cpMultiByte;
//
//	// 変換結果を返す
//	return(oRet);
//}


int Utf16ToUtf8(char *dest, size_t dest_size, wchar_t *src, size_t src_size);

inline void	MoveBuffer(unsigned	int	size, unsigned	int	num, unsigned	char**	buffer) {
	*buffer += (size*num);
}





bool PmxLoader::Load(const pmxString _filePath) {
	setlocale(LC_ALL, "Japanese");
	std::wstring wstr;
#ifdef UNICODE
	wstr = _filePath;
#else
	wstr = StringToWString(_filePath);
#endif // UNICODE

	IkBonenum = 0;

	//データロード
	FILE*	fp;
#ifdef UNICODE
	errno_t	error = fopen_s(&fp, WStringToString(wstr).c_str(), "rb");
#else
	errno_t	error = fopen_s(&fp, wstr.c_str(), "rb");
#endif // UNICODE


	if (error != 0) {//失敗
		//DebugLog("Load Fail \n\t %s\n", _filePath.c_str());
		return	false;
	}
	fseek(fp, 0, SEEK_END);
	unsigned	bufferSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	unsigned	char*	buffer = nullptr;
	buffer = new unsigned	char[bufferSize];

	unsigned char* head = buffer;
	fread(buffer, sizeof(unsigned char), bufferSize, fp);
	fclose(fp);
	//	データロード終わり

	Pmx::Header	header = { 0 };
	LoadPmxHeader(&header, &buffer);
	LoadPMXVertex(&header, &buffer);
	LoadPMXIndex(&header, &buffer);
	LoadPMXTexture(&header, &buffer, WStringToString(wstr).c_str());
	LoadPMXMaterial(&header, &buffer);
	LoadPMXBone(&header, &buffer);
	//LoadPMXMorph(&header, &buffer);
	//MovePMX(&header, &buffer);
	//LoadPMXRigid(&header, &buffer);
	//LoadPMXJoint(&header, &buffer);

	SafeDeleteArray(head);

	return true;
}

bool PmxLoader::LoadPmxHeader(Pmx::Header*	pHeader, unsigned char** buffer) {
	SetLoadDataArry(pHeader->magic, sizeof(unsigned char), 4, buffer);

	SetLoadData(&pHeader->version, sizeof(float), buffer);
	SetLoadData(&pHeader->variousDatasizeLength, sizeof(BYTE), buffer);
	//ここからデータ系の大きさ取得
	SetLoadData(&pHeader->encodeType, sizeof(unsigned	char), buffer);
	SetLoadData(&pHeader->appendUV, sizeof(unsigned	char), buffer);
	SetLoadData(&pHeader->vertexIndexSize, sizeof(unsigned	char), buffer);
	SetLoadData(&pHeader->textureIndexSize, sizeof(unsigned	char), buffer);
	SetLoadData(&pHeader->materialIndexSize, sizeof(unsigned	char), buffer);
	SetLoadData(&pHeader->boneIndexSize, sizeof(unsigned	char), buffer);
	SetLoadData(&pHeader->morphIndexSize, sizeof(unsigned	char), buffer);
	SetLoadData(&pHeader->rigidIndexSize, sizeof(unsigned	char), buffer);

	//モデルの名前
	SetLoadData(&pHeader->nameByteSize, sizeof(unsigned	int), buffer);
	MoveBuffer(sizeof(unsigned char), pHeader->nameByteSize, buffer);

	SetLoadData(&pHeader->nameEnglishByteSize, sizeof(unsigned	int), buffer);
	if (pHeader->nameEnglishByteSize > 0) {
		MoveBuffer(sizeof(unsigned	char), pHeader->nameEnglishByteSize, buffer);
	}
	//ここからコメント
	SetLoadData(&pHeader->commentByteSize, sizeof(unsigned	int), buffer);
	MoveBuffer(sizeof(unsigned	char), pHeader->commentByteSize, buffer);
	//コメント英語
	SetLoadData(&pHeader->commentEnglishByteSize, sizeof(unsigned	int), buffer);
	if (pHeader->commentEnglishByteSize > 0) {
		MoveBuffer(sizeof(unsigned	char), pHeader->commentEnglishByteSize, buffer);
	}

	return true;
}

bool	PmxLoader::LoadPMXVertex(Pmx::Header*	pHeader, unsigned char** buffer) {
	//頂点数
	unsigned int vertexnum;
	SetLoadData(&vertexnum, sizeof(unsigned	int), buffer);

	//頂点バッファ作成
	this->vertexBuffer.resize(vertexnum);

	//頂点格納
	for (unsigned int i = 0; i < vertexnum; i++) {
		SetLoadData(&vertexBuffer[i].x, sizeof(float), buffer);
		SetLoadData(&vertexBuffer[i].y, sizeof(float), buffer);
		SetLoadData(&vertexBuffer[i].z, sizeof(float), buffer);

		SetLoadData(&vertexBuffer[i].nx, sizeof(float), buffer);
		SetLoadData(&vertexBuffer[i].ny, sizeof(float), buffer);
		SetLoadData(&vertexBuffer[i].nz, sizeof(float), buffer);

		SetLoadData(&vertexBuffer[i].u, sizeof(float), buffer);
		SetLoadData(&vertexBuffer[i].v, sizeof(float), buffer);

		//		追加UV分とばす
		MoveBuffer(sizeof(Pmx::AppendixUV), pHeader->appendUV, buffer);

		//ウエイトタイプ
		unsigned char weightType = 0;
		SetLoadData(&weightType, sizeof(unsigned char), buffer);
		vertexBuffer[i].weighttype = weightType;
		switch (weightType)//ウェイトタイプでボーン変化
		{
			case	Pmx::Vertex::BDEF1:
				//MoveBuffer(pHeader->boneIndexSize, 1, buffer);
				SetLoadData(&vertexBuffer[i].index[0], pHeader->boneIndexSize, buffer);
				break;
			case	Pmx::Vertex::BDEF2:
				//MoveBuffer(pHeader->boneIndexSize, 2, buffer);
				SetLoadData(&vertexBuffer[i].index[0], pHeader->boneIndexSize, buffer);
				SetLoadData(&vertexBuffer[i].index[1], pHeader->boneIndexSize, buffer);
				//MoveBuffer(sizeof(float), 1, buffer);
				SetLoadData(&vertexBuffer[i].weight[0], sizeof(float), buffer);
				break;
			case	Pmx::Vertex::BDEF4:
				//MoveBuffer(pHeader->boneIndexSize, 4, buffer);
				SetLoadData(&vertexBuffer[i].index[0], pHeader->boneIndexSize, buffer);
				SetLoadData(&vertexBuffer[i].index[1], pHeader->boneIndexSize, buffer);
				SetLoadData(&vertexBuffer[i].index[2], pHeader->boneIndexSize, buffer);
				SetLoadData(&vertexBuffer[i].index[3], pHeader->boneIndexSize, buffer);
				SetLoadData(&vertexBuffer[i].weight[0], sizeof(float), buffer);
				SetLoadData(&vertexBuffer[i].weight[1], sizeof(float), buffer);
				SetLoadData(&vertexBuffer[i].weight[2], sizeof(float), buffer);
				SetLoadData(&vertexBuffer[i].weight[3], sizeof(float), buffer);
				//MoveBuffer(sizeof(float), 4, buffer);

				break;
			case	Pmx::Vertex::SDEF:
				//MoveBuffer(pHeader->boneIndexSize, 2, buffer);
				SetLoadData(&vertexBuffer[i].index[0], pHeader->boneIndexSize, buffer);
				SetLoadData(&vertexBuffer[i].index[1], pHeader->boneIndexSize, buffer);
				//MoveBuffer(sizeof(float), 1, buffer);
				SetLoadData(&vertexBuffer[i].weight[0], sizeof(float), buffer);
				MoveBuffer(sizeof(float), 3, buffer);
				MoveBuffer(sizeof(float), 3, buffer);
				MoveBuffer(sizeof(float), 3, buffer);
				break;
			default:
				break;
		}
		MoveBuffer(sizeof(float), 1, buffer);
	}


	vertex.resize(vertexBuffer.size());
	for (unsigned int i = 0; i < vertexBuffer.size(); ++i) {
		//このウエイトタイプで頂点シェーダを決める
		vertex[i].weighttype = vertexBuffer[i].weighttype;
		vertex[i].pos = XMFLOAT3(PMX_MESH_SCALE*vertexBuffer[i].x, PMX_MESH_SCALE*vertexBuffer[i].y, PMX_MESH_SCALE* vertexBuffer[i].z);
		vertex[i].normal = XMFLOAT3(vertexBuffer[i].nx, vertexBuffer[i].ny, vertexBuffer[i].nz);
		vertex[i].uv = XMFLOAT2(vertexBuffer[i].u, vertexBuffer[i].v);
		vertex[i].boneIndex[0] = vertexBuffer[i].index[0];
		vertex[i].boneIndex[1] = vertexBuffer[i].index[1];
		vertex[i].boneIndex[2] = vertexBuffer[i].index[2];
		vertex[i].boneIndex[3] = vertexBuffer[i].index[3];
		::CopyMemory(&vertex[i].weight, vertexBuffer[i].weight, sizeof(float) * 4);
	}


	return true;
}


bool	PmxLoader::LoadPMXIndex(Pmx::Header*	pHeader, unsigned char** buffer) {
	//頂点数
	unsigned int Indexnum;
	SetLoadData(&Indexnum, sizeof(unsigned int), buffer);
	this->indexBuffer.resize(Indexnum);


	for (unsigned int i = 0; i < Indexnum; i++) {
		SetLoadData(&indexBuffer[i], pHeader->vertexIndexSize, buffer);
	}
	return true;
}

bool	PmxLoader::LoadPMXMaterial(Pmx::Header*	pHeader, unsigned char** buffer) {
	//マテリアルの数
	unsigned int materialnum;
	SetLoadData(&materialnum, sizeof(unsigned int), buffer);


	unsigned	int	materialNameByte = 0;
	unsigned	int	materialEnglishNameByte = 0;

	this->materialBuffer.resize(materialnum);
	//pCMesh->m_pMateriale = new	MaterialeStr[pCMesh->m_MaterialNum];
	//memset(pCMesh->m_pMateriale, 0, sizeof(MaterialeStr)*pCMesh->m_MaterialNum);


	for (unsigned int i = 0; i < materialnum; i++) {
		//名前系
		SetLoadData(&materialNameByte, sizeof(unsigned	int), buffer);
		MoveBuffer(materialNameByte, 1, buffer);
		SetLoadData(&materialEnglishNameByte, sizeof(unsigned	int), buffer);
		MoveBuffer(materialEnglishNameByte, 1, buffer);
		SetLoadData(&materialBuffer[i].diffuse, sizeof(float) * 4, buffer);
		SetLoadData(&materialBuffer[i].specular, sizeof(float) * 3, buffer);
		SetLoadData(&materialBuffer[i].specular[3], sizeof(float), buffer);
		SetLoadData(&materialBuffer[i].emissive, sizeof(float) * 3, buffer);

		MoveBuffer(sizeof(BYTE), 1, buffer);//draw
		MoveBuffer(sizeof(float), 4, buffer);//edgecol
		MoveBuffer(sizeof(float), 1, buffer);//edge

		SetLoadData(&materialBuffer[i].textureEntry, pHeader->textureIndexSize, buffer);
		MoveBuffer(pHeader->textureIndexSize, 1, buffer);
		MoveBuffer(sizeof(BYTE), 1, buffer);

		BYTE	toonFlg = 0;
		SetLoadData(&toonFlg, sizeof(BYTE), buffer);
		switch (toonFlg) {
			case	0:
				MoveBuffer(pHeader->textureIndexSize, 1, buffer);
				break;
			case	1:
				MoveBuffer(sizeof(BYTE), 1, buffer);
				break;
			default:
				break;
		}
		unsigned	int	memoByte = 0;
		SetLoadData(&memoByte, sizeof(unsigned	int), buffer);
		MoveBuffer(memoByte, 1, buffer);
		SetLoadData(&materialBuffer[i].indexnum, sizeof(unsigned int), buffer);
	}


	material.resize(materialBuffer.size());
	for (unsigned int i = 0; i < materialBuffer.size(); i++) {
		CopyMaterial(material[i], materialBuffer[i]);
		//ここでPixelShaderを決める
		if (materialBuffer[i].textureEntry < texturefilepath.size()) {
			material[i].m_textureName = texturefilepath[materialBuffer[i].textureEntry].c_str();
		}
		else {

		}
		material[i].SetMaterialMeshCount(materialBuffer[i].indexnum);
	}

	return true;
}

bool	PmxLoader::LoadPMXTexture(Pmx::Header*	pHeader, unsigned char** buffer, const	char*	pFileName) {
	if (pHeader->encodeType == 0)//UTF16
	{
		CreateUTF16Texture(pHeader, buffer, pFileName);
	}
	if (pHeader->encodeType == 1)//UTF8
	{
		CreateUTF8Texture(pHeader, buffer, pFileName);
	}


	return true;
}

void	PmxLoader::CreateUTF16Texture(Pmx::Header*	pHeader, unsigned char** buffer, const	char*	pFileName) {
	//ここからテクスチャ
	unsigned	int texturenum;
	SetLoadData(&texturenum, sizeof(unsigned	int), buffer);//テクスチャの数
	unsigned	int	TextureByteNumber = 0;
	this->texturefilepath.resize(texturenum);

	wchar_t *p_TextureName;
	for (unsigned int i = 0; i < texturenum; i++) {
		//テクスチャーpath読み込み
		SetLoadData(&TextureByteNumber, sizeof(unsigned	int), buffer);
		p_TextureName = new wchar_t[(TextureByteNumber / 2) + 1];
		SetLoadData(p_TextureName, sizeof(wchar_t)*(TextureByteNumber / 2), buffer);
		p_TextureName[(TextureByteNumber / 2)] = L'\0';

		//ここから文字をUTF8に
		std::wstring ws(p_TextureName);

		ws = ws.substr(0, ws.find(L'*'));	// temp
		char *mbs = new char[ws.length() * MB_CUR_MAX + 1];
		wcstombs(mbs, ws.c_str(), ws.length() * MB_CUR_MAX + 1);//変換

		//ここから文字に作業階層追加
		std::string	tex(mbs);
		std::string work(pFileName);
		int	b = work.rfind("/");
		if (b != -1) {
			work = work.substr(0, b + 1);//作業階層ゲット
			tex = work + tex;
		}
#ifdef UNICODE
		this->texturefilepath[i] = StringToWString(tex);
#else
		this->texturefilepath[i] = tex;
#endif // UNICODE


		SafeDeleteArray(p_TextureName);
		SafeDeleteArray(mbs);
	}


}

void	PmxLoader::CreateUTF8Texture(Pmx::Header*	pHeader, unsigned char** buffer, const	char*	pFileName) {
	//ここからテクスチャ
	unsigned	int texturenum;
	SetLoadData(&texturenum, sizeof(unsigned	int), buffer);//テクスチャの数
	unsigned	int	TextureByteNumber = 0;
	this->texturefilepath.resize(texturenum);

	pmxString	p_TextureName;
	for (unsigned int i = 0; i < texturenum; i++) {
		//テクスチャーpath読み込み
		SetLoadData(&TextureByteNumber, sizeof(unsigned	int), buffer);
		SetLoadData(&p_TextureName, sizeof(wchar_t)*(TextureByteNumber / 2), buffer);
		p_TextureName[(TextureByteNumber / 2)] = L'\0';


		//ここから文字に作業階層追加
#ifdef UNICODE
		std::string	tex = WStringToString(p_TextureName);
#else
		std::string	tex = p_TextureName;
#endif // UNICODE
		std::string work(pFileName);
		int	b = work.rfind("/");
		if (b != -1) {
			work = work.substr(0, b + 1);//作業階層ゲット
			tex = work + tex;
		}
#ifdef UNICODE
		this->texturefilepath[i] = StringToWString(tex);
#else
		this->texturefilepath[i] = tex;
#endif // UNICODE

	}
}

bool PmxLoader::CreateMesh(SkinMeshObject *_mesh, DX11Device *dev) {

	_mesh->CreateGeometryObject(dev, nullptr, nullptr);
	//頂点バッファ
	VertexSkin *vertexBufferwork = new VertexSkin[vertexBuffer.size()];
	for (unsigned int i = 0; i < vertexBuffer.size(); ++i) {
		//このウエイトタイプで頂点シェーダを決める
		vertexBufferwork[i].weighttype = vertexBuffer[i].weighttype;
		vertexBufferwork[i].pos = XMFLOAT3(PMX_MESH_SCALE*vertexBuffer[i].x, PMX_MESH_SCALE*vertexBuffer[i].y, PMX_MESH_SCALE* vertexBuffer[i].z);
		vertexBufferwork[i].normal = XMFLOAT3(vertexBuffer[i].nx, vertexBuffer[i].ny, vertexBuffer[i].nz);
		vertexBufferwork[i].uv = XMFLOAT2(vertexBuffer[i].u, vertexBuffer[i].v);
		vertexBufferwork[i].boneIndex[0] = vertexBuffer[i].index[0];
		vertexBufferwork[i].boneIndex[1] = vertexBuffer[i].index[1];
		vertexBufferwork[i].boneIndex[2] = vertexBuffer[i].index[2];
		vertexBufferwork[i].boneIndex[3] = vertexBuffer[i].index[3];
		::CopyMemory(&vertexBufferwork[i].weight, vertexBuffer[i].weight, sizeof(float) * 4);

	}
	SkinMesh *mesh = new SkinMesh;
	mesh->CreateVertexBuffer(dev, vertexBufferwork, vertexBuffer.size());

	//インデックスバッファの作成
	unsigned int* indexBufferwork = new unsigned int[indexBuffer.size()];
	for (unsigned int i = 0; i < indexBuffer.size(); ++i) {
		indexBufferwork[i] = indexBuffer[i];
	}

	mesh->CreateIndexBuffer(dev, indexBufferwork, indexBuffer.size());

	SafeDeleteArray(vertexBufferwork);
	SafeDeleteArray(indexBufferwork);

	_mesh->SetMesh(mesh);


	for (unsigned int i = 0; i < materialBuffer.size(); i++) {
		PmxMaterialBase *material = new PmxMaterialBase;
		CopyMaterial(*material, materialBuffer[i]);
		//ここでPixelShaderを決める
		if (materialBuffer[i].textureEntry < texturefilepath.size()) {
			material->m_textureName = texturefilepath[materialBuffer[i].textureEntry].c_str();
			material->LoadTextureFromFile(dev);
		}
		else {

		}
		material->SetMaterialMeshCount(materialBuffer[i].indexnum);
		_mesh->SetMaterial(material);
	}


	CreateBone(&mesh->GetBone());
	CreateIKBone(&mesh->GetIKBone());

	return true;
}

void PmxLoader::CopyMaterial(PmxMaterialBase &material, const  Material& pmdMaterial) {
	material.SetDiffuse(pmdMaterial.diffuse);
	material.SetSpecular(pmdMaterial.specular);
	material.SetEmissive(pmdMaterial.emissive);
}

bool PmxLoader::LoadPMXBone(Pmx::Header*	pHeader, unsigned char** buffer) {
	unsigned	int Bonenum;
	SetLoadData(&Bonenum, sizeof(unsigned	int), buffer);//Boneの数
	this->Bonebuff.resize(Bonenum);

	if (pHeader->encodeType == 0)//UTF16
	{
		CreateUTF16Bone(pHeader, buffer);
	}
	if (pHeader->encodeType == 1)//UTF8
	{
		CreateUTF8Bone(pHeader, buffer);
	}


	return true;
}

bool   PmxLoader::CreateUTF16Bone(Pmx::Header*	pHeader, unsigned char** buffer) {
	//Boneの名前サイズ
	unsigned	int BoneNamesize;
	//unsigned	int EnglishBoneNamesize;

	for (unsigned int i = 0; i < this->Bonebuff.size(); i++) {
		BoneNamesize = 0;
		SetLoadData(&BoneNamesize, sizeof(unsigned int), buffer);
		wchar_t *p_boneName = new wchar_t[(BoneNamesize / 2) + 1];

		SetLoadData(p_boneName, sizeof(wchar_t)*(BoneNamesize / 2), buffer);
		p_boneName[(BoneNamesize / 2)] = L'\0';

		//ここから文字をUTF8に
		std::wstring ws(p_boneName);
		ws = ws.substr(0, ws.find(L'*'));	// temp
		char *mbs = new char[ws.length() * MB_CUR_MAX + 1];
		wcstombs(mbs, ws.c_str(), ws.length() * MB_CUR_MAX + 1);//変換

		std::string	bone(mbs);
		this->Bonebuff[i].boneName = bone;
		SafeDeleteArray(p_boneName);
		SafeDeleteArray(mbs);

		SetLoadData(&BoneNamesize, sizeof(unsigned	int), buffer);//テクスチャの数
		p_boneName = new wchar_t[(BoneNamesize / 2) + 1];

		SetLoadData(p_boneName, sizeof(wchar_t)*(BoneNamesize / 2), buffer);//テクスチャの数
		p_boneName[(BoneNamesize / 2)] = L'\0';

		//ここから文字をUTF8に
		std::wstring wsE(p_boneName);
		wsE = wsE.substr(0, wsE.find(L'*'));	// temp
		mbs = new char[wsE.length() * MB_CUR_MAX + 1];
		wcstombs(mbs, wsE.c_str(), wsE.length() * MB_CUR_MAX + 1);//変換

		std::string	boneEng(mbs);
		this->Bonebuff[i].boneEnglishName = boneEng;


		SafeDeleteArray(p_boneName);
		SafeDeleteArray(mbs);
		//ボーン位置
		SetLoadData(&Bonebuff[i].pos, sizeof(float) * 3, buffer);
		//親ボーンインデックス
		SetLoadData(&Bonebuff[i].ParentIndex, pHeader->boneIndexSize, buffer);
		//変形階層
		SetLoadData(&Bonebuff[i].tranceHyerarky, sizeof(unsigned int), buffer);
		//	ビットフラグ
		SetLoadData(&Bonebuff[i].bitflg, sizeof(unsigned short), buffer);

		if (Bonebuff[i].bitflg&Pmx::Bone::BIT_JOINT) {
			SetLoadData(&Bonebuff[i].IndexJoint, pHeader->boneIndexSize, buffer);
		}
		else {
			SetLoadData(&Bonebuff[i].Joint, sizeof(float) * 3, buffer);
		}

		if (Bonebuff[i].bitflg&(Pmx::Bone::BIT_GIVE_ROT | Pmx::Bone::BIT_GIVE_MOVE)) {
			SetLoadData(&Bonebuff[i].GiveIndex, pHeader->boneIndexSize, buffer);
			SetLoadData(&Bonebuff[i].Give, sizeof(float), buffer);
		}

		if (Bonebuff[i].bitflg&Pmx::Bone::BIT_FIX_AXIS) {
			SetLoadData(&Bonebuff[i].vFixAxis, sizeof(float) * 3, buffer);
		}

		if (Bonebuff[i].bitflg&Pmx::Bone::BIT_LOCAL_AXIS) {
			SetLoadData(&Bonebuff[i].vAxisX, sizeof(float) * 3, buffer);
			SetLoadData(&Bonebuff[i].vAxisZ, sizeof(float) * 3, buffer);
		}

		if (Bonebuff[i].bitflg&Pmx::Bone::BIT_EXT_PARENT) {
			SetLoadData(&Bonebuff[i].iExtParent, sizeof(int) * 3, buffer);
		}

		if (Bonebuff[i].bitflg&Pmx::Bone::BIT_IK) {
			IkBonenum++;
			SetLoadData(&Bonebuff[i].Ik.idxBone, pHeader->boneIndexSize, buffer);
			SetLoadData(&Bonebuff[i].Ik.nLoop, sizeof(int), buffer);
			SetLoadData(&Bonebuff[i].Ik.fLimitAng, sizeof(float), buffer);

			unsigned int iknum;
			SetLoadData(&iknum, sizeof(unsigned int), buffer);
			Bonebuff[i].Ik.aLink.resize(iknum);

			for (auto& l : Bonebuff[i].Ik.aLink) {
				SetLoadData(&l.idxBone, pHeader->boneIndexSize, buffer);
				SetLoadData(&l.bLimit, sizeof(unsigned char), buffer);
				if (l.bLimit) {
					SetLoadData(&l.vMin, sizeof(float) * 3, buffer);
					SetLoadData(&l.vMax, sizeof(float) * 3, buffer);
				}
			}
		}

	}
	return true;
}
bool  PmxLoader::CreateUTF8Bone(Pmx::Header*	pHeader, unsigned char** buffer) {
	//Boneの名前サイズ
	unsigned	int BoneNamesize;
	//unsigned	int EnglishBoneNamesize;

	for (unsigned int i = 0; i < this->Bonebuff.size(); i++) {
		SetLoadData(&BoneNamesize, sizeof(unsigned	int), buffer);
		pmxString p_boneName;

		SetLoadData(&p_boneName, sizeof(wchar_t)*(BoneNamesize / 2), buffer);
		p_boneName[(BoneNamesize / 2)] = L'\0';

#ifdef UNICODE
		std::string	bone = WStringToString(p_boneName);
#else
		std::string	bone = p_boneName;
#endif // UNICODE

		this->Bonebuff[i].boneName = bone;
		pmxString p_boneNameEng;

		SetLoadData(&BoneNamesize, sizeof(unsigned	int), buffer);
		SetLoadData(&p_boneNameEng, sizeof(wchar_t)*(BoneNamesize / 2), buffer);
		p_boneNameEng[(BoneNamesize / 2)] = L'\0';
#ifdef UNICODE
		bone = WStringToString(p_boneNameEng);
#else
		bone = p_boneNameEng;
#endif // UNICODE

		this->Bonebuff[i].boneEnglishName = bone;

		//ボーン位置
		SetLoadData(&Bonebuff[i].pos, sizeof(float) * 3, buffer);
		//親ボーンインデックス
		SetLoadData(&Bonebuff[i].ParentIndex, pHeader->boneIndexSize, buffer);
		//変形階層
		SetLoadData(&Bonebuff[i].tranceHyerarky, sizeof(unsigned int), buffer);
		//	ビットフラグ
		SetLoadData(&Bonebuff[i].bitflg, sizeof(unsigned short), buffer);

		if (Bonebuff[i].bitflg&Pmx::Bone::BIT_JOINT) {
			SetLoadData(&Bonebuff[i].IndexJoint, pHeader->boneIndexSize, buffer);
		}
		else {
			SetLoadData(&Bonebuff[i].Joint, sizeof(float) * 3, buffer);
		}

		if (Bonebuff[i].bitflg&(Pmx::Bone::BIT_GIVE_ROT | Pmx::Bone::BIT_GIVE_MOVE)) {
			SetLoadData(&Bonebuff[i].GiveIndex, pHeader->boneIndexSize, buffer);
			SetLoadData(&Bonebuff[i].Give, sizeof(float), buffer);
		}

		if (Bonebuff[i].bitflg&Pmx::Bone::BIT_FIX_AXIS) {
			SetLoadData(&Bonebuff[i].vFixAxis, sizeof(float) * 3, buffer);
		}

		if (Bonebuff[i].bitflg&Pmx::Bone::BIT_LOCAL_AXIS) {
			SetLoadData(&Bonebuff[i].vAxisX, sizeof(float) * 3, buffer);
			SetLoadData(&Bonebuff[i].vAxisZ, sizeof(float) * 3, buffer);
		}

		if (Bonebuff[i].bitflg&Pmx::Bone::BIT_EXT_PARENT) {
			SetLoadData(&Bonebuff[i].iExtParent, sizeof(int) * 3, buffer);
		}

		if (Bonebuff[i].bitflg&Pmx::Bone::BIT_IK) {
			IkBonenum++;
			SetLoadData(&Bonebuff[i].Ik.idxBone, pHeader->boneIndexSize, buffer);
			SetLoadData(&Bonebuff[i].Ik.nLoop, sizeof(int), buffer);
			SetLoadData(&Bonebuff[i].Ik.fLimitAng, sizeof(float), buffer);

			unsigned int iknum;
			SetLoadData(&iknum, sizeof(unsigned int), buffer);
			Bonebuff[i].Ik.aLink.resize(iknum);

			for (auto& l : Bonebuff[i].Ik.aLink) {
				SetLoadData(&l.idxBone, pHeader->boneIndexSize, buffer);
				SetLoadData(&l.bLimit, sizeof(unsigned char), buffer);
				if (l.bLimit) {
					SetLoadData(&l.vMin, sizeof(float) * 3, buffer);
					SetLoadData(&l.vMax, sizeof(float) * 3, buffer);
				}
			}
		}

	}
	return true;
}

void PmxLoader::CreateBone(std::vector<MMDBone>* b) {
	unsigned int size = Bonebuff.size();
	b->resize(size);
	for (unsigned int i = 0; i < size; ++i) {
		int parentIdx(-1), firstChildIdx(-1), siblingIdx(-1);
		if (Bonebuff[i].ParentIndex != 0xFFFF) parentIdx = Bonebuff[i].ParentIndex;
		for (unsigned int j = i + 1; j < size; ++j) {
			if (Bonebuff[i].ParentIndex == Bonebuff[j].ParentIndex) {
				siblingIdx = j;
				break;
			}
		}
		for (unsigned int j = 0; j < size; ++j) {
			if (i == Bonebuff[j].ParentIndex) {
				firstChildIdx = j;
				break;
			}
		}
		XMMATRIX modelLocalInitMat;

		modelLocalInitMat = XMMatrixTranslation(PMX_MESH_SCALE*Bonebuff[i].pos[0], PMX_MESH_SCALE*Bonebuff[i].pos[1], PMX_MESH_SCALE*Bonebuff[i].pos[2]);
		char boneName[21] = { 0 };	// ボーン名が20byteのときのために最後に0を追加
		memcpy(boneName, Bonebuff[i].boneName.c_str(), 20);
		(*b)[i].id = i;
		if (parentIdx != -1) {
			if (parentIdx < (int) b->size())
				(*b)[i].parent = &(*b)[parentIdx];
		}

		if (firstChildIdx != -1) (*b)[i].firstChild = &(*b)[firstChildIdx];
		if (siblingIdx != -1) (*b)[i].sibling = &(*b)[siblingIdx];
		(*b)[i].name = boneName;
		(*b)[i].type = 0;
		if (Bonebuff[i].bitflg&Pmx::Bone::BIT_IK) {
			(*b)[i].type = 7;
		}
		XMStoreFloat4x4(&(*b)[i].initMat, modelLocalInitMat);	// モデルローカル座標系
		XMStoreFloat4x4(&(*b)[i].offsetMat, XMMatrixInverse(&XMMatrixDeterminant(XMLoadFloat4x4(&(*b)[i].initMat)), XMLoadFloat4x4(&(*b)[i].initMat)));
	}

	class InitMatCalc {	// InitMatをボーンローカル座標系に変換する再帰関数を定義したクラス
	public:
		static void Run(MMDBone* me, XMFLOAT4X4 *parentoffsetMat) {
			if (me->firstChild) Run(me->firstChild, &me->offsetMat);
			if (me->sibling)	Run(me->sibling, parentoffsetMat);
			if (parentoffsetMat) {
				XMMATRIX work = XMLoadFloat4x4(&me->initMat);
				XMMATRIX work2 = XMLoadFloat4x4(parentoffsetMat);
				work *= work2;
				XMStoreFloat4x4(&me->initMat, work);
			}
		}
	};
	InitMatCalc::Run(&(*b)[0], 0);	// ボーンローカル座標系に変換
	for (unsigned int i = 0; i < size; ++i) (*b)[i].boneMat = (*b)[i].initMat;
}

void PmxLoader::CreateIKBone(std::vector<MMDIKBone>* p) {
	int iknum = 0;
	p->resize(IkBonenum);
	for (unsigned short i = 0; i < Bonebuff.size(); ++i) {
		if (Bonebuff[i].bitflg&Pmx::Bone::BIT_IK) {
			MMDIKBone pmdIkDataWithoutArray;
			pmdIkDataWithoutArray.boneIndex = i;
			pmdIkDataWithoutArray.effectorBoneIndex = Bonebuff[i].Ik.idxBone;
			pmdIkDataWithoutArray.controlWeight = Bonebuff[i].Ik.fLimitAng;
			pmdIkDataWithoutArray.numIterations = Bonebuff[i].Ik.nLoop;
			pmdIkDataWithoutArray.chainLength = Bonebuff[i].Ik.aLink.size();
			std::vector<unsigned short> ik_child_bone_index(pmdIkDataWithoutArray.chainLength);
			for (unsigned char j = 0; j < pmdIkDataWithoutArray.chainLength; ++j)
				ik_child_bone_index[j] = Bonebuff[i].Ik.aLink[j].idxBone;
			(*p)[iknum].boneIndex = pmdIkDataWithoutArray.boneIndex;

			(*p)[iknum].effectorBoneIndex = pmdIkDataWithoutArray.effectorBoneIndex;
			(*p)[iknum].chainLength = pmdIkDataWithoutArray.chainLength;
			(*p)[iknum].numIterations = pmdIkDataWithoutArray.numIterations;
			(*p)[iknum].controlWeight = pmdIkDataWithoutArray.controlWeight;
			(*p)[iknum].childBoneIndexVector = ik_child_bone_index;
			iknum++;
			if (iknum == IkBonenum) {

			}
		}
	}
}

bool PmxLoader::CreateMotionBone(std::vector<MMDBone>* b, std::vector<MMDIKBone>* p) {


	p->resize(ikBone.size());
	for (unsigned int i = 0; i < p->size(); i++) {
		(*p)[i] = ikBone[i];
	}

	b->resize(bone.size());
	for (unsigned int i = 0; i < b->size(); i++) {
		(*b)[i] = bone[i];
	}


	//b = &bone;

	return true;
}

bool PmxLoader::CreateMotionBone(std::vector<MMDBone> &b, std::vector<MMDIKBone> &p) {
	p.resize(ikBone.size());
	for (unsigned int i = 0; i < ikBone.size(); i++) {
		p[i] = ikBone[i];
	}
	b.resize(bone.size());
	for (unsigned int i = 0; i < bone.size(); i++) {
		b[i] = bone[i];
	}
	return true;
}

bool PmxLoader::LoadPMXMorph(Pmx::Header*	pHeader, unsigned char** buffer) {
	unsigned int num;
	SetLoadData(&num, sizeof(unsigned int), buffer);

	morph.resize(num);

	if (pHeader->encodeType == 0)//UTF16
	{
		CreateUTF16Morph(pHeader, buffer);
	}
	if (pHeader->encodeType == 1)//UTF8
	{
		CreateUTF8Morph(pHeader, buffer);
	}


	return true;
}
bool PmxLoader::MovePMX(Pmx::Header*	pHeader, unsigned char** buffer) {
	unsigned int num;
	SetLoadData(&num, sizeof(unsigned int), buffer);
	for (unsigned int i = 0; i < num; i++) {
		unsigned int work;
		SetLoadData(&work, sizeof(unsigned int), buffer);
		MoveBuffer(work, 1, buffer);
		SetLoadData(&work, sizeof(unsigned int), buffer);
		MoveBuffer(work, 1, buffer);
		MoveBuffer(1, 1, buffer);
		SetLoadData(&work, sizeof(unsigned int), buffer);

		for (unsigned int j = 0; j < work; j++) {
			byte w;
			SetLoadData(&w, 1, buffer);
			switch (w) {
				case 0:
					MoveBuffer(pHeader->boneIndexSize, 1, buffer);
					break;
				case 1:
					MoveBuffer(pHeader->morphIndexSize, 1, buffer);
					break;
			}
		}

	}
	return true;
}
bool PmxLoader::LoadPMXRigid(Pmx::Header*	pHeader, unsigned char** buffer) {
	unsigned int num;
	SetLoadData(&num, sizeof(unsigned int), buffer);

	rigid_body.resize(num);
	if (pHeader->encodeType == 0)//UTF16
	{
		CreateUTF16Rigid(pHeader, buffer);
	}
	if (pHeader->encodeType == 1)//UTF8
	{
		CreateUTF8Rigid(pHeader, buffer);
	}
	return true;
}
bool PmxLoader::LoadPMXJoint(Pmx::Header*	pHeader, unsigned char** buffer) {
	unsigned int num;
	SetLoadData(&num, sizeof(unsigned int), buffer);

	joint.resize(num);


	if (pHeader->encodeType == 0)//UTF16
	{
		CreateUTF16Joint(pHeader, buffer);
	}
	if (pHeader->encodeType == 1)//UTF8
	{
		CreateUTF8Joint(pHeader, buffer);
	}
	return true;
}
bool PmxLoader::CreateUTF16Morph(Pmx::Header*	pHeader, unsigned char** buffer) {
	//Boneの名前サイズ
	unsigned	int morphNamesize;
	//unsigned	int EnglishmorphNamesize;

	for (unsigned int i = 0; i < this->morph.size(); i++) {
		morphNamesize = 0;
		SetLoadData(&morphNamesize, sizeof(unsigned int), buffer);
		wchar_t *p_morphName = new wchar_t[(morphNamesize / 2) + 1];

		SetLoadData(p_morphName, sizeof(wchar_t)*(morphNamesize / 2), buffer);
		p_morphName[(morphNamesize / 2)] = L'\0';

		//ここから文字をUTF8に
		std::wstring ws(p_morphName);
		ws = ws.substr(0, ws.find(L'*'));	// temp
		char *mbs = new char[ws.length() * MB_CUR_MAX + 1];
		wcstombs(mbs, ws.c_str(), ws.length() * MB_CUR_MAX + 1);//変換

		std::string	bone(mbs);
		morph[i].Name = bone;
		SafeDeleteArray(p_morphName);
		SafeDeleteArray(mbs);

		SetLoadData(&morphNamesize, sizeof(unsigned	int), buffer);//テクスチャの数
		p_morphName = new wchar_t[(morphNamesize / 2) + 1];

		SetLoadData(p_morphName, sizeof(wchar_t)*(morphNamesize / 2), buffer);//テクスチャの数
		p_morphName[(morphNamesize / 2)] = L'\0';

		//ここから文字をUTF8に
		std::wstring wsE(p_morphName);
		wsE = wsE.substr(0, wsE.find(L'*'));	// temp
		mbs = new char[wsE.length() * MB_CUR_MAX + 1];
		wcstombs(mbs, wsE.c_str(), wsE.length() * MB_CUR_MAX + 1);//変換

		std::string	boneEng(mbs);
		//morph[i].Name = boneEng;
		SafeDeleteArray(p_morphName);
		SafeDeleteArray(mbs);

		SetLoadData(&morph[i].ControlPanel, sizeof(byte), buffer);
		SetLoadData(&morph[i].Type, sizeof(byte), buffer);
		SetLoadData(&morph[i].DataNum, sizeof(int), buffer);

		switch (morph[i].Type) {
			case 0:
				morph[i].Group = new Pmx::PMX_MORPH_GROUP[morph[i].DataNum];
				break;
			case 1:
				morph[i].Vertex = new Pmx::PMX_MORPH_VERTEX[morph[i].DataNum];
				break;
			case 2:
				morph[i].UV = new Pmx::PMX_MORPH_UV[morph[i].DataNum];
				break;
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
				morph[i].Bone = new Pmx::PMX_MORPH_BONE[morph[i].DataNum];
				break;
			case 8:
				morph[i].Material = new Pmx::PMX_MORPH_MATERIAL[morph[i].DataNum];
				break;
		}



		for (int j = 0; j < morph[i].DataNum; j++) {
			switch (morph[i].Type) {
				case 0:
					SetLoadData(&morph[i].Group[j].Index, pHeader->morphIndexSize, buffer);
					SetLoadData(&morph[i].Group[j].Ratio, sizeof(float), buffer);
					break;
				case 1:
					SetLoadData(&morph[i].Vertex[j].Index, pHeader->vertexIndexSize, buffer);
					SetLoadData(&morph[i].Vertex[j].Offset, sizeof(float) * 3, buffer);
					break;
				case 2:
					SetLoadData(&morph[i].UV[j].Index, pHeader->vertexIndexSize, buffer);
					SetLoadData(&morph[i].UV[j].Offset, sizeof(float) * 4, buffer);
					break;
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					SetLoadData(&morph[i].Bone[j].Index, pHeader->boneIndexSize, buffer);
					SetLoadData(&morph[i].Bone[j].Offset, sizeof(float) * 3, buffer);
					SetLoadData(&morph[i].Bone[j].Quat, sizeof(float) * 4, buffer);
					break;
				case 8:
					SetLoadData(&morph[i].Material[j].Index, pHeader->materialIndexSize, buffer);
					SetLoadData(&morph[i].Material[j].CalcType, 1, buffer);
					SetLoadData(&morph[i].Material[j].Diffuse, sizeof(float) * 4, buffer);
					SetLoadData(&morph[i].Material[j].Specular, sizeof(float) * 3, buffer);
					SetLoadData(&morph[i].Material[j].SpecularPower, sizeof(float), buffer);
					SetLoadData(&morph[i].Material[j].Ambient, sizeof(float) * 3, buffer);
					SetLoadData(&morph[i].Material[j].EdgeColor, sizeof(float) * 4, buffer);
					SetLoadData(&morph[i].Material[j].EdgeSize, sizeof(float), buffer);
					SetLoadData(&morph[i].Material[j].TextureScale, sizeof(float) * 4, buffer);
					SetLoadData(&morph[i].Material[j].SphereTextureScale, sizeof(float) * 4, buffer);
					SetLoadData(&morph[i].Material[j].ToonTextureScale, sizeof(float) * 4, buffer);
					break;
			}
		}
	}
	return true;
}

bool PmxLoader::CreateUTF8Morph(Pmx::Header*	pHeader, unsigned char** buffer) {
	//Boneの名前サイズ
	unsigned	int morphNamesize;
	//unsigned	int EnglishmorphNamesize;

	for (unsigned int i = 0; i < this->morph.size(); i++) {
		morphNamesize = 0;
		SetLoadData(&morphNamesize, sizeof(unsigned	int), buffer);
		pmxString p_morphName;

		SetLoadData(&p_morphName, sizeof(wchar_t)*(morphNamesize / 2), buffer);
		p_morphName[(morphNamesize / 2)] = L'\0';

#ifdef UNICODE
		std::string	bone = WStringToString(p_morphName);
#else
		std::string	bone = p_morphName;
#endif // UNICODE
		this->morph[i].Name = bone;
		pmxString p_morphNameEng;

		SetLoadData(&morphNamesize, sizeof(unsigned	int), buffer);
		SetLoadData(&p_morphNameEng, sizeof(wchar_t)*(morphNamesize / 2), buffer);
		p_morphNameEng[(morphNamesize / 2)] = L'\0';
#ifdef UNICODE
		bone = WStringToString(p_morphNameEng);
#else
		bone = p_morphNameEng;
#endif // UNICODE
		
		//this->morph[i].Name = bone;

		SetLoadData(&morph[i].ControlPanel, sizeof(byte), buffer);
		SetLoadData(&morph[i].Type, sizeof(byte), buffer);
		SetLoadData(&morph[i].DataNum, sizeof(int), buffer);
		switch (morph[i].Type) {
			case 0:
				morph[i].Group = new Pmx::PMX_MORPH_GROUP[morph[i].DataNum];
				break;
			case 1:
				morph[i].Vertex = new Pmx::PMX_MORPH_VERTEX[morph[i].DataNum];
				break;
			case 2:
				morph[i].UV = new Pmx::PMX_MORPH_UV[morph[i].DataNum];
				break;
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
				morph[i].Bone = new Pmx::PMX_MORPH_BONE[morph[i].DataNum];
				break;
			case 8:
				morph[i].Material = new Pmx::PMX_MORPH_MATERIAL[morph[i].DataNum];
				break;
		}



		for (int j = 0; j < morph[i].DataNum; j++) {
			switch (morph[i].Type) {
				case 0:
					SetLoadData(&morph[i].Group[j].Index, pHeader->morphIndexSize, buffer);
					SetLoadData(&morph[i].Group[j].Ratio, sizeof(float), buffer);
					break;
				case 1:
					SetLoadData(&morph[i].Vertex[j].Index, pHeader->vertexIndexSize, buffer);
					SetLoadData(&morph[i].Vertex[j].Offset, sizeof(float) * 3, buffer);
					break;
				case 2:
					SetLoadData(&morph[i].UV[j].Index, pHeader->vertexIndexSize, buffer);
					SetLoadData(&morph[i].UV[j].Offset, sizeof(float) * 4, buffer);
					break;
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					SetLoadData(&morph[i].Bone[j].Index, pHeader->boneIndexSize, buffer);
					SetLoadData(&morph[i].Bone[j].Offset, sizeof(float) * 3, buffer);
					SetLoadData(&morph[i].Bone[j].Quat, sizeof(float) * 4, buffer);
					break;
				case 8:
					SetLoadData(&morph[i].Material[j].Index, sizeof(pHeader->materialIndexSize), buffer);
					SetLoadData(&morph[i].Material[j].CalcType, 1, buffer);
					SetLoadData(&morph[i].Material[j].Diffuse, sizeof(float) * 4, buffer);
					SetLoadData(&morph[i].Material[j].Specular, sizeof(float) * 3, buffer);
					SetLoadData(&morph[i].Material[j].SpecularPower, sizeof(float), buffer);
					SetLoadData(&morph[i].Material[j].Ambient, sizeof(float) * 3, buffer);
					SetLoadData(&morph[i].Material[j].EdgeColor, sizeof(float) * 4, buffer);
					SetLoadData(&morph[i].Material[j].EdgeSize, sizeof(float), buffer);
					SetLoadData(&morph[i].Material[j].TextureScale, sizeof(float) * 4, buffer);
					SetLoadData(&morph[i].Material[j].SphereTextureScale, sizeof(float) * 4, buffer);
					SetLoadData(&morph[i].Material[j].ToonTextureScale, sizeof(float) * 4, buffer);
					break;
			}
		}

	}
	return true;
}

bool PmxLoader::CreateUTF16Rigid(Pmx::Header*	pHeader, unsigned char** buffer) {
	//pmxString p_morphNameEng;
	std::wstring ws;
	std::string	bone;
	for (unsigned int i = 0; i < rigid_body.size(); i++) {
		unsigned int morphNamesize = 0;
		SetLoadData(&morphNamesize, sizeof(unsigned int), buffer);
		wchar_t *p_morphName = new wchar_t[(morphNamesize / 2) + 1];

		SetLoadData(p_morphName, sizeof(wchar_t)*(morphNamesize / 2), buffer);
		p_morphName[(morphNamesize / 2)] = L'\0';

		//ここから文字をUTF8に
		ws.assign(p_morphName);
		ws = ws.substr(0, ws.find(L'*'));	// temp
		char *mbs = new char[ws.length() * MB_CUR_MAX + 1];
		wcstombs(mbs, ws.c_str(), ws.length() * MB_CUR_MAX + 1);//変換

		bone.assign(mbs);
		rigid_body[i].Name = bone;
		SafeDeleteArray(p_morphName);
		SafeDeleteArray(mbs);

		SetLoadData(&morphNamesize, sizeof(unsigned	int), buffer);
		MoveBuffer(sizeof(wchar_t)*(morphNamesize / 2), 1, buffer);



		SetLoadData(&rigid_body[i].BoneIndex, pHeader->boneIndexSize, buffer);
		SetLoadData(&rigid_body[i].RigidBodyGroupIndex, sizeof(BYTE), buffer);
		SetLoadData(&rigid_body[i].RigidBodyGroupTarget, sizeof(WORD), buffer);
		SetLoadData(&rigid_body[i].ShapeType, sizeof(BYTE), buffer);

		for (int j = 0; j < 3; j++) {
			rigid_body[i].Shape[j] = 0;
		}
		SetLoadData(&rigid_body[i].Shape, sizeof(float) * 3, buffer);

		for (int j = 0; j < 3; j++) {
			rigid_body[i].Position[j] = 0;
		}
		SetLoadData(&rigid_body[i].Position, sizeof(float) * 3, buffer);

		for (int j = 0; j < 3; j++) {
			rigid_body[i].Rotation[j] = 0;
		}
		SetLoadData(&rigid_body[i].Rotation, sizeof(float) * 3, buffer);

		SetLoadData(&rigid_body[i].RigidBodyWeight, sizeof(float), buffer);
		SetLoadData(&rigid_body[i].RigidBodyPosDim, sizeof(float), buffer);
		SetLoadData(&rigid_body[i].RigidBodyRotDim, sizeof(float), buffer);
		SetLoadData(&rigid_body[i].RigidBodyRecoil, sizeof(float), buffer);
		SetLoadData(&rigid_body[i].RigidBodyFriction, sizeof(float), buffer);

		SetLoadData(&rigid_body[i].RigidBodyType, sizeof(BYTE), buffer);

	}


	return true;

}
bool PmxLoader::CreateUTF8Rigid(Pmx::Header*	pHeader, unsigned char** buffer) {

	for (unsigned int i = 0; i < rigid_body.size(); i++) {
		unsigned	int morphNamesize = 0;
		SetLoadData(&morphNamesize, sizeof(unsigned	int), buffer);
		pmxString p_morphName;

		SetLoadData(&p_morphName, sizeof(wchar_t)*(morphNamesize / 2), buffer);
		p_morphName[(morphNamesize / 2)] = L'\0';

#ifdef UNICODE
		std::string	bone = WStringToString(p_morphName);
#else
		std::string	bone = p_morphName;
#endif // UNICODE

		rigid_body[i].Name = bone;

		pmxString p_morphNameEng;
		SetLoadData(&morphNamesize, sizeof(unsigned	int), buffer);
		SetLoadData(&p_morphNameEng, sizeof(wchar_t)*(morphNamesize / 2), buffer);


		SetLoadData(&rigid_body[i].BoneIndex, pHeader->boneIndexSize, buffer);
		SetLoadData(&rigid_body[i].RigidBodyGroupIndex, sizeof(BYTE), buffer);
		SetLoadData(&rigid_body[i].RigidBodyGroupTarget, sizeof(WORD), buffer);
		SetLoadData(&rigid_body[i].ShapeType, sizeof(BYTE), buffer);

		for (int j = 0; j < 3; j++) {
			rigid_body[i].Shape[j] = 0;
		}
		SetLoadData(&rigid_body[i].Shape, sizeof(float) * 3, buffer);

		for (int j = 0; j < 3; j++) {
			rigid_body[i].Position[j] = 0;
		}
		SetLoadData(&rigid_body[i].Position, sizeof(float) * 3, buffer);

		for (int j = 0; j < 3; j++) {
			rigid_body[i].Rotation[j] = 0;
		}
		SetLoadData(&rigid_body[i].Rotation, sizeof(float) * 3, buffer);

		SetLoadData(&rigid_body[i].RigidBodyWeight, sizeof(float), buffer);
		SetLoadData(&rigid_body[i].RigidBodyPosDim, sizeof(float), buffer);
		SetLoadData(&rigid_body[i].RigidBodyRotDim, sizeof(float), buffer);
		SetLoadData(&rigid_body[i].RigidBodyRecoil, sizeof(float), buffer);
		SetLoadData(&rigid_body[i].RigidBodyFriction, sizeof(float), buffer);

		SetLoadData(&rigid_body[i].RigidBodyType, sizeof(BYTE), buffer);
	}
	return true;
}

bool PmxLoader::CreateUTF16Joint(Pmx::Header*	pHeader, unsigned char** buffer) {
	for (unsigned int i = 0; i < joint.size(); i++) {
		unsigned int morphNamesize = 0;
		SetLoadData(&morphNamesize, sizeof(unsigned int), buffer);
		wchar_t *p_morphName = new wchar_t[(morphNamesize / 2) + 1];

		SetLoadData(p_morphName, sizeof(wchar_t)*(morphNamesize / 2), buffer);
		p_morphName[(morphNamesize / 2)] = L'\0';

		//ここから文字をUTF8に
		std::wstring ws(p_morphName);
		ws = ws.substr(0, ws.find(L'*'));	// temp
		char *mbs = new char[ws.length() * MB_CUR_MAX + 1];
		wcstombs(mbs, ws.c_str(), ws.length() * MB_CUR_MAX + 1);//変換

		std::string	bone(mbs);
		joint[i].Name = bone;
		SafeDeleteArray(p_morphName);
		SafeDeleteArray(mbs);
		pmxString p_morphNameEng;
		SetLoadData(&morphNamesize, sizeof(unsigned	int), buffer);
		MoveBuffer(sizeof(wchar_t)*(morphNamesize / 2), 1, buffer);


		SetLoadData(&joint[i].Type, 1, buffer);
		SetLoadData(&joint[i].RigidBodyAIndex, pHeader->rigidIndexSize, buffer);
		SetLoadData(&joint[i].RigidBodyBIndex, pHeader->rigidIndexSize, buffer);

		SetLoadData(&joint[i].Position, sizeof(float) * 3, buffer);
		SetLoadData(&joint[i].Rotation, sizeof(float) * 3, buffer);

		SetLoadData(&joint[i].ConstrainPositionMin, sizeof(float) * 3, buffer);
		SetLoadData(&joint[i].ConstrainPositionMax, sizeof(float) * 3, buffer);
		SetLoadData(&joint[i].ConstrainRotationMin, sizeof(float) * 3, buffer);
		SetLoadData(&joint[i].ConstrainRotationMax, sizeof(float) * 3, buffer);

		SetLoadData(&joint[i].SpringPosition, sizeof(float) * 3, buffer);
		SetLoadData(&joint[i].SpringRotation, sizeof(float) * 3, buffer);

	}
	return true;
}
bool PmxLoader::CreateUTF8Joint(Pmx::Header*	pHeader, unsigned char** buffer) {
	for (unsigned int i = 0; i < joint.size(); i++) {
		unsigned	int morphNamesize = 0;
		SetLoadData(&morphNamesize, sizeof(unsigned	int), buffer);
		pmxString p_morphName;

		SetLoadData(&p_morphName, sizeof(wchar_t)*(morphNamesize / 2), buffer);
		p_morphName[(morphNamesize / 2)] = L'\0';

#ifdef UNICODE
		std::string	bone = WStringToString(p_morphName);
#else
		std::string	bone = p_morphName;
#endif // UNICODE

		joint[i].Name = bone;

		pmxString p_morphNameEng;
		SetLoadData(&morphNamesize, sizeof(unsigned	int), buffer);
		SetLoadData(&p_morphNameEng, sizeof(wchar_t)*(morphNamesize / 2), buffer);


		SetLoadData(&joint[i].Type, 1, buffer);
		SetLoadData(&joint[i].RigidBodyAIndex, pHeader->rigidIndexSize, buffer);
		SetLoadData(&joint[i].RigidBodyBIndex, pHeader->rigidIndexSize, buffer);

		SetLoadData(&joint[i].Position, sizeof(float) * 3, buffer);
		SetLoadData(&joint[i].Rotation, sizeof(float) * 3, buffer);

		SetLoadData(&joint[i].ConstrainPositionMin, sizeof(float) * 3, buffer);
		SetLoadData(&joint[i].ConstrainPositionMax, sizeof(float) * 3, buffer);
		SetLoadData(&joint[i].ConstrainRotationMin, sizeof(float) * 3, buffer);
		SetLoadData(&joint[i].ConstrainRotationMax, sizeof(float) * 3, buffer);

		SetLoadData(&joint[i].SpringPosition, sizeof(float) * 3, buffer);
		SetLoadData(&joint[i].SpringRotation, sizeof(float) * 3, buffer);

	}
	return true;
}


bool PmxLoader::LoadFromFile(const tstring& filename) {
	return this->Load(filename);
}
bool PmxLoader::LoadFromMemory(void *memory, size_t size) {
	(void) memory;
	(void) size;
	return false;
}
int PmxLoader::GetMeshNum() {
	return 1;
}
int PmxLoader::GetVertexSize(int index) {
	return vertexBuffer.size() * sizeof(VertexSkin);
}
void *PmxLoader::GetVertexBuffer(int index) {
	return &vertex[0];
}
size_t PmxLoader::GetVertexStride() {
	return sizeof(VertexSkin);
}
size_t PmxLoader::GetIndexBufferSize(int Index) {
	return indexBuffer.size() * sizeof(unsigned int);
}
void *PmxLoader::GetIndexBuffer(int index) {
	return &indexBuffer[0];
}

PmxMaterialBase *PmxLoader::GetMaterial(int index) {
	return &material[index];
}
size_t PmxLoader::GetMaterialNum() {
	return material.size();
}