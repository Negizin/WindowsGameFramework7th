//!*******************************************************
//!	TsBuffer.h
//!
//!	�C���f�b�N�X�o�b�t�@�A���_�o�b�t�@�AC�o�b�t�@�𒊏ۉ�
//!
#pragma once
#include	<d3d11.h>
#include	"../Utilities/NameObject/NameObject.h"

class DX11Device;
class DeviceContext;

class Buffer : public NameObject {
public:
	Buffer() :m_buffer(nullptr), m_bufferSize(0) {};
	virtual ~Buffer() { SafeRelease(m_buffer); }

	//=============================================
	// ! GetBuffer
	// Dx11�@�`���Ńo�b�t�@�|�C���^���擾
	// @return true is success
	ID3D11Buffer* GetBuffer()const { return m_buffer; };

	//=============================================
	// ! Create
	// Create DirectX Device & SwapChain & DeviceContext
	// @pram buffer	�f�o�C�X�쐬�������ɂȂ�o�b�t�@�f�[�^
	// @return true is success
	/*bool SetD3DBufferAndSize(ID3D11Buffer* buffer, UINT size)
	{
		m_buffer = buffer;
		m_bufferSize = size;
		return TRUE;
	};*/
	bool SetBufferSize(UINT size) {
		m_bufferSize = size;
		return TRUE;
	}

	//! Get Size
	UINT GetBufferSize()const { return m_bufferSize; }

	//!	Map
	bool Map(__in DeviceContext *dev,
		__in void *pData,
		__in size_t size);


protected:
	//!CreateBuffer
	bool CreateBuffer(__in DX11Device *dev,
		__in void * pData,
		__in size_t size,
		__in UINT cpuAct,
		__in UINT type);
private:
	ID3D11Buffer* m_buffer;
	UINT		  m_bufferSize;
};