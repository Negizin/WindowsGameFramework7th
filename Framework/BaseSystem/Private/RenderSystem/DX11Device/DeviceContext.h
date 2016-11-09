//!*******************************************************
//!	DeviceContext.h
//!
//!	DeviceContext.
//!

#pragma once
#include "DX11Device.h"
#include "../Shader/ShaderUtility.h"
#include <DirectXMath.h>
using namespace DirectX;

class DX11Device;
class RenderTarget;
class DepthStencil;
class Texture;
class Viewport;
class Effect;
class CBuffer;
class Camera;
class VertexBuffer;
class IndexBuffer;
class SamplerState;
class RasterizerState;
class DepthStencilState;

class DeviceContext {
public:
	static const UINT	 MAX_RTs = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;			//RenderTragetView�̍ő吔
	DeviceContext(DX11Device* device, ID3D11DeviceContext* pDevContext);
	~DeviceContext();

	//=============================================
	// ! Clear
	// �o�C���h����Ă���RTV�y��DSV�̃N���A
	// @pram color	RTV���N���A����F
	void Clear(XMFLOAT4& color = XMFLOAT4(0, 1, .5f, .5f));

	//=============================================
	// ! SetScreenRTV
	// �f�B�X�v���C�ɏo�͂���RenderTargetView(RTV)��o�^
	// �����̃��\�b�h�͖����I�ɌĂԕK�v�͂Ȃ�
	// @pram rtv SwapChain����擾�����o�b�N�o�b�t�@�Ő������ꂽRTV
	// @return Success is true
	bool SetScreenRTV(RenderTarget* rtv);

	//=============================================
	// ! SetRT
	// RenderTargetView(RTV)��o�^���˗�
	// @pram idx 0 - 7 
	// @pram rt  RTV
	// @return Success is true
	bool SetRT(UINT idx, RenderTarget* rt);


	//=============================================
	// ! SetDepth
	// DepthStencilView��o�^
	// @pram dsv 
	// @return Success is true
	bool SetDepthStencil(DepthStencil* dsv);

	bool SetMainDepthStencil(DepthStencil* dsv);

	//=============================================
	// ! SetTexture
	// �e�N�X�`����o�^
	// @pram slotIndex 0-7
	// @pram texture �e�N�X�`���@OR�@RTV
	// @pram type �ǂ̃V�F�[�_�Ƀo�C���h���邩(�ʏ��PS)
	// @return Success is true
	bool SetTexture(UINT slotIndex, const Texture* texture, SHADER_TYPE type);

	//=============================================
	// ! ApplyRenderTargets
	// RenderTarget�̕ύX��o�^
	// �����̃��\�b�h�̓p�X�̊J�n���ɖ����I�ɌĂяo�����ƁB
	// @return Success is true
	bool ApplyRenderTargets();

	//=============================================
	// ! SetViewport
	// viewport��o�^
	// @pram viewport Viewport
	// @return Success is true
	bool SetViewport(Viewport* viewport);


	//=============================================
	// ! SetEffect
	// �V�F�[�_�̏W����o�^
	// @pram shaderEffect
	// @return Success is true

	bool SetEffect(Effect* Effect);

	//=============================================
	// ! GetScreenRTV
	// �f�B�X�v���C�Ƀo�C���h����Ă���RTV���擾
	// @return �f�B�X�v���C�Ƀo�C���h����Ă���RTV
	RenderTarget* GetScreenRTV()const { return m_mainRenderTarget; }

	//=============================================
	// ! DrawIndex
	// IndexDraw
	void DrawIndex(UINT index, UINT startSlot = 0, UINT indexLocation = 0) {
		m_pDeviceContext->DrawIndexed(index, startSlot, indexLocation);
	}

	//=============================================
	// ! ResetDrawCallCount
	// DrawCall�̃J�E���g�̃��Z�b�g
	void ResetDrawCallCount() {
		m_drawCallCount = 0;
	}

	//=============================================
	// ! SetTopology
	// �g�|���W�[���Z�b�g
	// @pram topology D3D_PRIMITIVE_TOPOLOGY
	// IndexDraw
	void SetTopology(D3D_PRIMITIVE_TOPOLOGY topology) {
		m_pDeviceContext->IASetPrimitiveTopology(topology);
	}

	ID3D11DeviceContext* GetDeviceContext() {
		return m_pDeviceContext;
	};

	bool ChangeCBuffer(CBuffer * cbuffer, void * pData, size_t sz);

	bool SetAndChangeCBuffer(CBuffer* cbuffer, void * pData, size_t size);

	bool SetCBuffer(CBuffer * cbuffer);

	bool ApplyInputLayout();
	//=============================================
	// ! Draw
	// �`��
	// @pram topology D3D_PRIMITIVE_TOPOLOGY
	// Draw
	bool Draw(int vtxNum, int startSlot = 0);

	//=============================================
	// ! DrawIndex
	// �`��
	// @pram topology D3D_PRIMITIVE_TOPOLOGY
	// Draw
	bool DrawIndex(int startnum, int vtxNum, int startSlot = 0);

	bool SetVertexBuffer(VertexBuffer*);
	bool SetIndexBuffer(IndexBuffer*);

	bool SetSamplerState(SamplerState * pSampler, int registerIndex, SHADER_TYPE ShaderType);
	bool SetDepthStencilState(DepthStencilState * pDepthStencil);
	bool SetRasterizerState(RasterizerState * pRasterState);
	bool ApplyDepthStencil();
	bool ApplyRasterizer();


	void SetMainCamera(Camera *_camera) { m_mainCamera = _camera; }
	Camera *GetMainCamera();
	void GetMainCamera(Camera *camera) { m_mainCamera = camera; }
	D3D11_DEVICE_CONTEXT_TYPE GetContextType() { return m_pDeviceContext->GetType(); }
	DepthStencil *GetMainDSV() { return m_mainDepthStencil; }
	bool ClearVertexBuffer();
	bool ClearIndexBuffer();
	bool ClearCBuffer(int index = -1, SHADER_TYPE type = SHADER_TYPE::ALL_SHADER);
private:

	DX11Device*				m_pDevice;
	ID3D11DeviceContext*	m_pDeviceContext;
	ID3D11RasterizerState*	m_pRasterizeState;
	Effect*				    m_bindEffect;
	bool					m_activeShaders[SHADER_INDEX::MAX_IDX];
	RenderTarget *			m_renderTarget[MAX_RTs];
	RenderTarget *			m_mainRenderTarget;
	DepthStencil *			m_depthStencil;
	DepthStencil *			m_mainDepthStencil;
	RasterizerState *                    m_pRasterizerState;
	DepthStencilState*                m_pDepthStencilState;
	Camera*			   	    m_mainCamera;
	int						m_drawCallCount;

};