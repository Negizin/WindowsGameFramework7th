//!*******************************************************
//!	TsCBuffer.h
//!
//!	CBuffer�N���X�̒�`
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
	// �]����̃V�F�[�_��ݒ肷��
	// �Q�ȏ�̃V�F�[�_�ɓ]������ꍇ��OR�Ō�������B
	// @pram type 
	// @return true is success
	void BindShaderType(SHADER_TYPE type) { m_bindShaderType = type; }

	//=============================================
	// ! GetBindShaderType
	// �]����̃V�F�[�_���擾����
	// @return �V�F�[�_�̎�ށB�����l��Unknown
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
