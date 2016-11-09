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
	static const UINT	 MAX_RTs = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;			//RenderTragetViewの最大数
	DeviceContext(DX11Device* device, ID3D11DeviceContext* pDevContext);
	~DeviceContext();

	//=============================================
	// ! Clear
	// バインドされているRTV及びDSVのクリア
	// @pram color	RTVをクリアする色
	void Clear(XMFLOAT4& color = XMFLOAT4(0, 1, .5f, .5f));

	//=============================================
	// ! SetScreenRTV
	// ディスプレイに出力するRenderTargetView(RTV)を登録
	// ※このメソッドは明示的に呼ぶ必要はない
	// @pram rtv SwapChainから取得したバックバッファで生成されたRTV
	// @return Success is true
	bool SetScreenRTV(RenderTarget* rtv);

	//=============================================
	// ! SetRT
	// RenderTargetView(RTV)を登録を依頼
	// @pram idx 0 - 7 
	// @pram rt  RTV
	// @return Success is true
	bool SetRT(UINT idx, RenderTarget* rt);


	//=============================================
	// ! SetDepth
	// DepthStencilViewを登録
	// @pram dsv 
	// @return Success is true
	bool SetDepthStencil(DepthStencil* dsv);

	bool SetMainDepthStencil(DepthStencil* dsv);

	//=============================================
	// ! SetTexture
	// テクスチャを登録
	// @pram slotIndex 0-7
	// @pram texture テクスチャ　OR　RTV
	// @pram type どのシェーダにバインドするか(通常はPS)
	// @return Success is true
	bool SetTexture(UINT slotIndex, const Texture* texture, SHADER_TYPE type);

	//=============================================
	// ! ApplyRenderTargets
	// RenderTargetの変更を登録
	// ※このメソッドはパスの開始時に明示的に呼び出すこと。
	// @return Success is true
	bool ApplyRenderTargets();

	//=============================================
	// ! SetViewport
	// viewportを登録
	// @pram viewport Viewport
	// @return Success is true
	bool SetViewport(Viewport* viewport);


	//=============================================
	// ! SetEffect
	// シェーダの集合を登録
	// @pram shaderEffect
	// @return Success is true

	bool SetEffect(Effect* Effect);

	//=============================================
	// ! GetScreenRTV
	// ディスプレイにバインドされているRTVを取得
	// @return ディスプレイにバインドされているRTV
	RenderTarget* GetScreenRTV()const { return m_mainRenderTarget; }

	//=============================================
	// ! DrawIndex
	// IndexDraw
	void DrawIndex(UINT index, UINT startSlot = 0, UINT indexLocation = 0) {
		m_pDeviceContext->DrawIndexed(index, startSlot, indexLocation);
	}

	//=============================================
	// ! ResetDrawCallCount
	// DrawCallのカウントのリセット
	void ResetDrawCallCount() {
		m_drawCallCount = 0;
	}

	//=============================================
	// ! SetTopology
	// トポロジーをセット
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
	// 描画
	// @pram topology D3D_PRIMITIVE_TOPOLOGY
	// Draw
	bool Draw(int vtxNum, int startSlot = 0);

	//=============================================
	// ! DrawIndex
	// 描画
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