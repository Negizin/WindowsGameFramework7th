#include	"ResourceManager.h"
#include	"../DX11Device/DX11Device.h"

#define ASSIGN_INTERFACE(T,Name)\
 std::unordered_map<HASH,T*> ResourceManager::Name;\
/*!-----------------------------------------------------------------/\
//@brief	RegisterResource										 \		 
//																	 \
//		特殊化テンプレート関数										 \
//																	 \
//@Param[in]	objectポインタ										 \
//@Param[in]	名前												 \
//@Auther   宮原敏史												 \
//@Date		2016/11/01												 \
//-----------------------------------------------------------------*/\
template<>\
bool ResourceManager::RegisterResource(T* p,const tstring& name)\
{\
		return ResourceManager_Register(Name, p, name);\
}\
/*!-----------------------------------------------------------------/\
//@brief	Find													 \
//																	 \
//		特殊化テンプレート関数										 \
//																	 \
//@Param[in]	名前								　　　　		 \
//@Param[out]	オブジェクトのポインタ								 \
//@Auther   宮原敏史												 \
//@Date		2016/11/01												 \
//-----------------------------------------------------------------*/\
template<>\
T* ResourceManager::Find(const tstring& name)\
{\
		return ResourceManager_Find(Name, name); \
}\

//-------------------------------------------------------------------------------
//  Find Resource Manager Template
//-------------------------------------------------------------------------------
template<class T>
bool ResourceManager_Register(std::unordered_map<HASH, T*>& map,T* pObj,const tstring& name)
{
	HASH hash = UT::StringToHash(name);
	bool hResult = map.find(hash) == map.end();
	if (hResult == true)
	{
		std::pair<HASH, T*> pair;
		pair.first = hash;
		pair.second = pObj;

		map.insert(pair);
	}

	return hResult;
}

//-------------------------------------------------------------------------------
//  Register Resource Manager Template
//-------------------------------------------------------------------------------
template<class T>
T* ResourceManager_Find(std::unordered_map<HASH, T*>& map,const tstring& name)
{
	HASH hash = UT::StringToHash(name);

	auto it = map.find(hash);
	if (it == map.end())
		return nullptr;

	return it->second;
}

/*!-----------------------------------------------------------------/
//@brief	RegisterResouce
//
//  リソースの登録
//
//@Param[in]	登録するオブジェクトのポインタ
//@Param[in]	登録する名前
//@Auther   宮原敏史
//@Date		2016/11/01
//-----------------------------------------------------------------*/

template<typename T>
static bool ResourceManager::RegisterResource(T* pObject, const tstring& name){

	(void)pObject;
	(void)name;
	return false;
}

/*!-----------------------------------------------------------------/
//@brief	Find
//
//  探索
//
//@Param[in]	検索する名前
//@Param[out]	オブジェクトのポインタ
//@Auther   宮原敏史
//@Date		2016/11/01	
//-----------------------------------------------------------------*/
template<typename T>
static T* ResourceManager::Find(const tstring& name){
	(void)name;
	return nullptr;
}


bool ResourceManager::Initialize(DX11Device* pDev)
{
	m_pDevice = pDev;
	InitializeSampler(pDev);

	return true;
}


bool ResourceManager::InitializeSampler(DX11Device* pDev){

	D3D11_SAMPLER_DESC desc;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

	desc.BorderColor[0] =
		desc.BorderColor[1] =
		desc.BorderColor[2] =
		desc.BorderColor[3] = 0.0f;

	desc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;

	desc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
	desc.MaxAnisotropy = 16;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;

	desc.MipLODBias = 0;
	std::pair<HASH, SamplerState*> pair(UT::StringToHash(_T("Default")), pDev->CreateSamplerState(desc));
	m_SamplerLibrary.insert(pair);

	return true;

}

DX11Device* ResourceManager::m_pDevice = nullptr;
ASSIGN_INTERFACE(SamplerState, m_SamplerLibrary);
ASSIGN_INTERFACE(MeshObject, m_pMeshLibrary);
ASSIGN_INTERFACE(Texture2D, m_FileTextureLibray);
ASSIGN_INTERFACE(Skeleton, m_pSkeletonLibrary);
ASSIGN_INTERFACE(RenderTarget, m_pRenderTargetLibrary);
ASSIGN_INTERFACE(DepthStencil, m_pDepthStencilLibrary);
ASSIGN_INTERFACE(Effect, m_pEffectLibrary);