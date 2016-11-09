/*!-----------------------------------------------------------------/
//@brief	DX11Device.h
//
//  �f�o�C�X�N���X�A�f�o�C�X�N���X�C���^�[�t�F�C�X�̒�`
//
//@Auther   �{���q�j
//@Date     2016/10/22
//-----------------------------------------------------------------*/
#pragma once
#include "../DX11Include/DX11IncludeHeader.h"
#include "DeviceContext.h"

class DeviceContext;
class SamplerState;

// Dx11 Device Intarface
class  IDX11Device {
public:
	//get device contetxt
	virtual DeviceContext * GetDC()const = 0;
	virtual ID3D11Device * GetDevD3D()const = 0;
	virtual IDXGISwapChain *	 GetSC()const = 0;
private:

};

//Dx11	Device Class
class DX11Device :public IDX11Device {
public:
	static const UINT	 MAX_DDC = 6;			//DeffardContext�̍ő吔
	//=============================================
	// ! Get DeviceContext
	DeviceContext* GetDC()const override;

	//=============================================
	// ! Get DirectX Device Pointer
	ID3D11Device*	 GetDevD3D()const override { return m_device; }

	//=============================================
	// ! Get DirectX Swap Chain
	IDXGISwapChain*	 GetSC()const override { return m_swapChain; }


	//=============================================
	// ! CreateDevice
	// Create DirectX Device & SwapChain & DeviceContext
	// @pram hWnd	DirectX�̕`��^�[�Q�b�g�E�B���h�E�n���h��
	//		 width & height Back Buffer Size
	// @return true is success
	bool CreateDevice(HWND hWnd, int width, int height);


	//=============================================
	// ! Flip
	// FlipScreen
	// @return true is success
	bool Flip();


	SamplerState*  CreateSamplerState(const D3D11_SAMPLER_DESC& desc);

	void Release();
private:

	//=============================================
	// ! GetRefreshRato
	// PC ���j�^�̃��t���b�V�����[�g���擾
	// @pram _out refreshRato x = ���q�@y =����
	//		 ��L�̈����͖߂�l�Ƃ��Ĉ����B
	//		 width & height ��ʃT�C�Y
	// @return true is success
	bool GetRefreshRato(UINT refreshRatox, UINT refreshRatoy, const UINT width, const UINT height);

	//=============================================
	// ! LoadDefaultShader
	// �f�t�H���g�V�F�[�_�̃��[�h
	// @return true is success
	bool LoadDefaultShader();

	//=============================================
	// ! CreateAndSetRaster
	// ���X�^���C�U�̍쐬�Ɠo�^
	// @return true is success
	bool CreateAndSetRaster();


	bool CreateDeffardContext();
private:

	ID3D11Device*		m_device;
	IDXGISwapChain*		m_swapChain;
	D3D_DRIVER_TYPE		m_driverType;
	D3D_FEATURE_LEVEL	m_featureLevel;
	DeviceContext*		m_deviceContext;
	DeviceContext*		m_DefferadContext[MAX_DDC];
};

