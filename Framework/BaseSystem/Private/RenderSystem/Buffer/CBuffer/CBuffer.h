//!*******************************************************
//!	TsCBuffer.h
//!
//!	CBufferクラスの定義
//!
#pragma once

#include	"../Buffer.h"
#include	"../../ShaderResource/ShaderResouce.h"
#include	"../../Shader/ShaderUtility.h"

class DeviceContext;
class CBuffer :
	public Buffer,
	public ShaderResource {
public:
	CBuffer();
	virtual ~CBuffer();

	//=============================================
	// ! BindShaderType
	// 転送先のシェーダを設定する
	// ２つ以上のシェーダに転送する場合はORで結合する。
	// @pram type 
	// @return true is success
	void BindShaderType(SHADER_TYPE type) { m_bindShaderType = type; }

	//=============================================
	// ! GetBindShaderType
	// 転送先のシェーダを取得する
	// @return シェーダの種類。初期値はUnknown
	SHADER_TYPE GetBindShaderType()const { return m_bindShaderType; }

	virtual bool UpdateCBuffer(DeviceContext* pContext) { return TRUE; }
	virtual bool ApplyCBuffer(DeviceContext* pContext) { return TRUE; }


	bool CreateCBuffer(__in DX11Device *dev,
		__in void * pData,
		__in size_t size);

	bool CreateCBuffer(__in void * pData, __in size_t size);
private:
	SHADER_TYPE m_bindShaderType;
};
