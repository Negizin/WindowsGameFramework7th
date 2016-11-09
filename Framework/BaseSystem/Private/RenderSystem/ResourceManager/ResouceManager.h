/*!-----------------------------------------------------------------/
//@brief	ResouceManager
//
//  リソースマネージャー
//
//@Auther   宮原敏史
//@Date     2016/10/30
//-----------------------------------------------------------------*/
#pragma once
#include <unordered_map>
#include "../Utilities/File/File.h"

class DX11Device;
class SamplerState;
class MeshObject;
class Texture2D;
class Skeleton;
class RenderTarget;
class DepthStencil;
class Effect;

class ResourceManager
{
public:
	static bool Initialize(DX11Device * pDev);

	template<typename T>
	static bool RegisterResource(T* pObject, const tstring &name);

	template<typename T>
	static T* Find(const tstring& name);

private:
	static bool InitializeSampler(DX11Device* pDev);

	static DX11Device* m_pDevice;
	static std::unordered_map<HASH, SamplerState*> m_SamplerLibrary;
	static std::unordered_map<HASH, MeshObject*>   m_pMeshLibrary;
	static std::unordered_map<HASH, Texture2D*>     m_FileTextureLibray;
	static std::unordered_map<HASH, Skeleton*>     m_pSkeletonLibrary;
	static std::unordered_map<HASH, RenderTarget*>     m_pRenderTargetLibrary;
	static std::unordered_map<HASH, DepthStencil*>     m_pDepthStencilLibrary;
	static std::unordered_map<HASH, Effect*>     m_pEffectLibrary;
};