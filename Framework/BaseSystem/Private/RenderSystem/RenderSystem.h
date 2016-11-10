/*! =====================================================================================
@file		RenderSystem.h
@brief
@author
@date
====================================================================================== */
#pragma once
#include	"Utilities\NameObject\NameObject.h"
#include	"SystemResource\RenderFlow.h"
#include	"DX11Device\DX11Device.h"

class DX11Device;
class DeviceContext;
class Texture;
class DrawQueue;

class RenderSystem :public NameObject {
public:
	RenderSystem();
	virtual ~RenderSystem();

	/*! =====================================================================================
	@brief	初期化処理（デバイス生成）
	@param	HWND
	@return	bool
	====================================================================================== */
	bool	Initialize(HWND _hWnd);

	/*! =====================================================================================
	@brief	描画要求受付開始（描画用キュー・RTV,D・バッファクリア）
	@param	void
	@return void
	====================================================================================== */
	HRESULT	StartReceivingDrawObject();

	/*! =====================================================================================
	@brief	描画処理
	@param	void
	@return void
	====================================================================================== */
	virtual bool Render();

	//RenderFlowとDrawQueueの構造体
	struct FlowAndQue {
		RenderFlow *m_pFlow = nullptr;
		DrawQueue  *m_pQueue = nullptr;

		bool Render(DeviceContext *pDc) {
				//DebugLog("Draw Fail !!\n");
			if (!pDc || !m_pQueue || !m_pFlow) {
				return false;
			}
			m_pFlow->Render(pDc, m_pQueue);
			return true;
		}
	};

	enum class TARGET_FLOW {
		PRE_RENDERER,
		DEFAULT_RENDERER,
		POST_RENDERER,
	};





	bool	SetDrawQue(DrawQueue* pDrawQue, TARGET_FLOW = TARGET_FLOW::DEFAULT_RENDERER);
	bool	SetShaderFlow(RenderFlow* pFlow, TARGET_FLOW = TARGET_FLOW::DEFAULT_RENDERER);
	bool	LoadShaderResourceFromXML(DX11Device* pDev, const tstring&name);
	bool	LoadRenderSystemFromXML(DX11Device* pDev, const tstring&name);

	Texture*	FindTextureResource(const tstring & name);

	
	static const DX11Device*	GetDevice();

protected:
	//デバイス
	static	DX11Device*		m_pDevice;

	//レンダリング・システムリソース

	//std::vector<TsLight*>		m_lights;
	std::vector<Texture*>		m_shaderResourceList;
	std::vector<DrawQueue*>		m_drawque;

	FlowAndQue m_PreFlowAndQue;		//shadow生成
	FlowAndQue m_FlowAndQue;		//GBuffer生成
	//パーティクル
	//UI
	FlowAndQue m_PostFlowAndQue;	//PostEffect生成
};