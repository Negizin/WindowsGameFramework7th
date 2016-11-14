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
	@brief	�����������i�f�o�C�X�����j
	@param	HWND
	@return	bool
	====================================================================================== */
	bool	Initialize(HWND _hWnd);

	/*! =====================================================================================
	@brief	�`�揈��
	@param	void
	@return void
	====================================================================================== */
	virtual bool Render();

	//RenderFlow��DrawQueue�̍\����
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





	static bool	SetDrawQue(DrawQueue* pDrawQue, TARGET_FLOW = TARGET_FLOW::DEFAULT_RENDERER);
	static bool	SetShaderFlow(RenderFlow* pFlow, TARGET_FLOW = TARGET_FLOW::DEFAULT_RENDERER);
	static bool	LoadShaderResourceFromXML(DX11Device* pDev, const tstring&name);
	static bool	LoadRenderSystemFromXML(DX11Device* pDev, const tstring&name);
	static bool	LoadRenderSystemFromXML(const tstring& name);

	Texture*	FindTextureResource(const tstring & name);


	static  DX11Device*	GetDevice();

protected:
	//�f�o�C�X
	static	DX11Device*		m_pDevice;

	//�����_�����O�E�V�X�e�����\�[�X

	//std::vector<TsLight*>		m_lights;
	static std::vector<Texture*>		m_shaderResourceList;
	static std::vector<DrawQueue*>		m_drawque;

	static FlowAndQue m_PreFlowAndQue;		//shadow����
	static FlowAndQue m_FlowAndQue;		//GBuffer����
	//�p�[�e�B�N��
	//UI
	static FlowAndQue m_PostFlowAndQue;	//PostEffect����
};