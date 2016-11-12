#pragma once

#include	"../Buffer/CBuffer/CBuffer.h"
#include	"../ShaderResource/Texture/Texture.h"

class DX11Device;
class DeviceContext;



class MaterialBase : public CBuffer {
public:
	MaterialBase();
	virtual ~MaterialBase();
	virtual bool ApplyMaterial(DeviceContext* context);
	virtual bool UpdateMaterial(DeviceContext* context);
	virtual bool CreateMaterial(DX11Device* pDevice);
	virtual bool SetTexture(Texture2D *pTex);
	virtual bool LoadTextureFromFile(DX11Device* pDevice);
	virtual Texture2D* GetTexture()const;

public:
	tstring m_textureName;

protected:
	bool m_isUpdate;
	Texture2D*   m_pTexture;
};