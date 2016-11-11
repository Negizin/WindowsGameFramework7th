#include	"DeviceContext.h"

#include	 "../ViewPort/ViewPort.h"
#include	"../Effect/Effect.h"
#include	"../SystemResource/RenderFlow.h"
#include	"../ShaderResource/Texture/RenderTarget/RenderTarget.h"
#include	"../ShaderResource/Texture/DepthStencil/DepthStencil.h"
#include	"../State/SamplerState.h"
#include	"../State/RasterizerState.h"
#include	"../State/DepthStencilState.h"

#include	"../Buffer/CBuffer/CBuffer.h"
#include	"../Buffer/IndexBuffer.h"
#include	"../Buffer/VertexBuffer.h"

#include	"../../../../GameObjectClasses/Camera/Camera.h"


using namespace DirectX;

//! Constructor
DeviceContext::DeviceContext(DX11Device* pDev, ID3D11DeviceContext* pCotext)
	:m_pDeviceContext(pCotext) {
	m_pDevice = pDev;
	m_mainDepthStencil = nullptr;
	m_mainCamera = nullptr;
	for (int i = 0; i < MAX_RTs; i++) {
		m_renderTarget[i] = nullptr;
	}
	m_mainRenderTarget = nullptr;
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

};

//! Destructor
DeviceContext::~DeviceContext() {
	SafeDelete(m_mainRenderTarget);
	SafeDelete(m_mainDepthStencil);
	SafeRelease(m_pDeviceContext);
}


//! clear color & depth buffer
void DeviceContext::Clear(XMFLOAT4& color /* 0x~~~~~~ */) {

	float col[4] = { color.x, color.y, color.z, color.w };

	if (m_pDeviceContext) {
		//! crear rendertargets
		for (int i = 0; i < MAX_RTs; ++i) {
			if (m_renderTarget[i])
				m_pDeviceContext->ClearRenderTargetView(m_renderTarget[i]->GetRTV(), &col[0]);
		}

		//! crear depth stencil view
		if (m_depthStencil)
			m_pDeviceContext->ClearDepthStencilView(m_depthStencil->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}

//! 実際にスクリーンに反映されるレンダーターゲットを設定する
bool DeviceContext::SetScreenRTV(RenderTarget * pRtv) {
	if (m_pDeviceContext == nullptr)
		return FALSE;

	m_mainRenderTarget = pRtv;
	return TRUE;
}


//! RenderTargetの変更を適用する
bool DeviceContext::ApplyRenderTargets() {
	if (m_pDeviceContext == nullptr)
		return FALSE;

	ID3D11RenderTargetView * renderTargets[MAX_RTs];
	ID3D11DepthStencilView * dsv = nullptr;

	if (m_depthStencil != nullptr) {
		dsv = m_depthStencil->GetDSV();
	}

	int rtNum = 0;
	for (; rtNum < MAX_RTs; ++rtNum) {
		if (m_renderTarget[rtNum] == nullptr)
			break;
		else
			renderTargets[rtNum] = m_renderTarget[rtNum]->GetRTV();
	}

	if (rtNum == 0) {
		return FALSE;
	}
	m_pDeviceContext->OMSetRenderTargets(rtNum, renderTargets, dsv);

	return TRUE;
}

//! Set texture
bool DeviceContext::SetTexture(UINT slotIndex,
	const Texture* texture,
	SHADER_TYPE type) {
	if (m_pDeviceContext == nullptr) return FALSE;

	//! Shader Resource View の取得
	ID3D11ShaderResourceView* srv = nullptr;
	if (texture != nullptr)
		srv = texture->GetSRV();
	else
		return FALSE;

	// テクスチャをgpuに設定
	switch (type) {
		case VERTEX_SHADER:		m_pDeviceContext->VSSetShaderResources(slotIndex, 1, &srv); break;
		case PIXEL_SHADER:		m_pDeviceContext->PSSetShaderResources(slotIndex, 1, &srv); break;
		case GEOMETRY_SHADER:	m_pDeviceContext->GSSetShaderResources(slotIndex, 1, &srv); break;
		case HULL_SHADER:		m_pDeviceContext->HSSetShaderResources(slotIndex, 1, &srv); break;
		case DOMAIN_SHADER:		m_pDeviceContext->DSSetShaderResources(slotIndex, 1, &srv); break;
		case COMPUTE_SHADER:	m_pDeviceContext->CSSetShaderResources(slotIndex, 1, &srv);	break;
		default:
			return FALSE;
	}
	return TRUE;
}

//! Draw Call
bool DeviceContext::Draw(int vtxNum, int startSlot) {
	if (m_pDeviceContext == nullptr)
		return FALSE;

	bool isActiveVSandPS = m_activeShaders[VS_IDX] & m_activeShaders[PS_IDX];

	if (isActiveVSandPS) {
		m_pDeviceContext->Draw(vtxNum, startSlot);
		m_drawCallCount++;
	}
	else {
		return FALSE;
	}
	return TRUE;
}

//=============================================
// ! DrawIndex
// 描画
// @pram topology D3D_PRIMITIVE_TOPOLOGY
// Draw
bool DeviceContext::DrawIndex(int startnum, int vtxNum, int startSlot) {
	if (m_pDeviceContext == nullptr)
		return FALSE;

	bool isActiveVSandPS = m_activeShaders[VS_IDX] & m_activeShaders[PS_IDX];

	if (isActiveVSandPS) {
		m_pDeviceContext->DrawIndexed(vtxNum, startnum, startSlot);
		m_drawCallCount++;
	}
	else {
		return FALSE;
	}
	return TRUE;
}

bool DeviceContext::SetSamplerState(SamplerState * pSampler, int registerIndex, SHADER_TYPE ShaderType) {
	if (m_pDeviceContext == nullptr) return false;
	ID3D11SamplerState* pD3DSampler = nullptr;
	if (pSampler != nullptr)
		pD3DSampler = pSampler->GetSamplerState();
	else
		return false;

	switch (ShaderType) {
		case VERTEX_SHADER:	m_pDeviceContext->VSSetSamplers(registerIndex, 1, &pD3DSampler);
		case PIXEL_SHADER:	m_pDeviceContext->PSSetSamplers(registerIndex, 1, &pD3DSampler);
		case GEOMETRY_SHADER:	m_pDeviceContext->GSSetSamplers(registerIndex, 1, &pD3DSampler);
		case HULL_SHADER:	m_pDeviceContext->HSSetSamplers(registerIndex, 1, &pD3DSampler);
		case DOMAIN_SHADER:	m_pDeviceContext->DSSetSamplers(registerIndex, 1, &pD3DSampler);
		case COMPUTE_SHADER:	m_pDeviceContext->CSSetSamplers(registerIndex, 1, &pD3DSampler);
		default:
			return false;
	}
	return true;
}

//! レンダーターゲットを設定する。(この時点ではまだデバイスには反映されない。)
bool DeviceContext::SetRT(UINT index, RenderTarget* view) {
	if (m_pDeviceContext == nullptr)
		return FALSE;

	if ((unsigned) index > MAX_RTs) {
		return FALSE;
	}
	m_renderTarget[index] = view;

	return TRUE;
}

//! Set Depth Stencil
bool DeviceContext::SetDepthStencil(DepthStencil* dsv) {
	if (m_pDeviceContext == nullptr)
		return FALSE;

	m_depthStencil = dsv;
	return TRUE;
}

bool DeviceContext::SetMainDepthStencil(DepthStencil* dsv) {
	if (m_pDeviceContext == nullptr)
		return FALSE;

	m_mainDepthStencil = dsv;
	return TRUE;

}

//! Set View port
bool DeviceContext::SetViewport(Viewport* viewport) {
	if (m_pDeviceContext == nullptr)
		return FALSE;

	if (viewport == nullptr)
		return FALSE;
	m_pDeviceContext->RSSetViewports(1, viewport->GetD3DViewport());

	return TRUE;
}
//! Apply Inputlayout
bool DeviceContext::ApplyInputLayout() {
	if (m_pDeviceContext == nullptr)
		return FALSE;

	if (m_activeShaders[VS_IDX] == FALSE)
		return FALSE;

	if (m_bindEffect == nullptr)
		return FALSE;

	auto inputLayout = m_bindEffect->GetInputLayout();
	m_pDeviceContext->IASetInputLayout(inputLayout);

	return TRUE;
}

Camera *DeviceContext::GetMainCamera() {
	if (m_mainCamera == nullptr) {
		//static Camera defaultCamera;
		//return &defaultCamera;
	}
	return m_mainCamera;
}

// ! SetShader
bool DeviceContext::SetEffect(Effect* Effect) {
	//if (!m_bindEffect)return FALSE;

	//=========================================
	//! シェーダのアクティブフラグを初期化
	//=========================================
	for (int i = 0; i < SHADER_INDEX::MAX_IDX; ++i) {
		m_activeShaders[i] = FALSE;
	}

	//パイプラインクラスがnullの場合すべてのシェーダを初期化
	if (Effect == nullptr) {
		m_pDeviceContext->VSSetShader(nullptr, nullptr, 0);
		m_pDeviceContext->PSSetShader(nullptr, nullptr, 0);
		m_pDeviceContext->GSSetShader(nullptr, nullptr, 0);
		m_pDeviceContext->CSSetShader(nullptr, nullptr, 0);
		m_pDeviceContext->HSSetShader(nullptr, nullptr, 0);
		m_pDeviceContext->DSSetShader(nullptr, nullptr, 0);

		return FALSE;
	}

	//=========================================
	//! アクティブシェーダの更新
	//=========================================
	if (Effect->GetVertexShader() && Effect->GetVertexShader()->GetShader())
		m_activeShaders[VS_IDX] = TRUE;
	if (Effect->GetPixelShader() && Effect->GetPixelShader()->GetShader())
		m_activeShaders[PS_IDX] = TRUE;
	if (Effect->GetGeometryShader() && Effect->GetGeometryShader()->GetShader())
		m_activeShaders[GS_IDX] = TRUE;
	if (Effect->GetHullShader() && Effect->GetHullShader()->GetShader())
		m_activeShaders[HS_IDX] = TRUE;
	if (Effect->GetDomainShader() && Effect->GetDomainShader()->GetShader())
		m_activeShaders[DS_IDX] = TRUE;
	if (Effect->GetComputeShader() && Effect->GetComputeShader()->GetShader())
		m_activeShaders[CS_IDX] = TRUE;

	//=========================================
	//! アクティブシェーダをコンテキストに登録
	//=========================================

	if (m_activeShaders[VS_IDX])
		m_pDeviceContext->VSSetShader(Effect->GetVertexShader()->GetShader(), nullptr, 0);
	else
		m_pDeviceContext->VSSetShader(nullptr, nullptr, 0);

	if (m_activeShaders[PS_IDX])
		m_pDeviceContext->PSSetShader(Effect->GetPixelShader()->GetShader(), nullptr, 0);
	else
		m_pDeviceContext->PSSetShader(nullptr, nullptr, 0);

	if (m_activeShaders[GS_IDX])
		m_pDeviceContext->GSSetShader(Effect->GetGeometryShader()->GetShader(), nullptr, 0);
	else
		m_pDeviceContext->GSSetShader(nullptr, nullptr, 0);

	if (m_activeShaders[HS_IDX])
		m_pDeviceContext->HSSetShader(Effect->GetHullShader()->GetShader(), nullptr, 0);
	else
		m_pDeviceContext->HSSetShader(nullptr, nullptr, 0);

	if (m_activeShaders[DS_IDX])
		m_pDeviceContext->DSSetShader(Effect->GetDomainShader()->GetShader(), nullptr, 0);
	else
		m_pDeviceContext->DSSetShader(nullptr, nullptr, 0);


	//=========================================
	// VertexShader Or PixelShader 
	// 設定されていないときはグラボがクラッシュする。
	//=========================================
	if ((m_activeShaders[VS_IDX] &&
		m_activeShaders[PS_IDX]) == FALSE) {
		//DebugLog("VertexShader OR PixelShader = null\n");
		return FALSE;
	}
	m_bindEffect = Effect;
	return FALSE;

}


bool DeviceContext::SetAndChangeCBuffer(CBuffer* cbuffer,
	void * pData,
	size_t size) {
	if (m_pDeviceContext == nullptr)
		return FALSE;

	bool hr;
	hr = ChangeCBuffer(cbuffer, pData, size);
	if (hr == FALSE)return FALSE;

	hr = SetCBuffer(cbuffer);
	if (hr == FALSE) return FALSE;

	return TRUE;
}

bool DeviceContext::SetCBuffer(CBuffer * cbuffer) {
	if (m_pDeviceContext == nullptr)
		return FALSE;

	if (cbuffer == nullptr)
		return FALSE;

	ID3D11Buffer* buffer = cbuffer->GetBuffer();

	auto shaderType = cbuffer->GetBindShaderType();

	if (buffer == nullptr)
		return FALSE;

	if (ShaderUT::IsVS(shaderType))
		m_pDeviceContext->VSSetConstantBuffers(cbuffer->GetRegisterIndex(), 1, &buffer);
	if (ShaderUT::IsPS(shaderType))
		m_pDeviceContext->PSSetConstantBuffers(cbuffer->GetRegisterIndex(), 1, &buffer);
	if (ShaderUT::IsGS(shaderType))
		m_pDeviceContext->CSSetConstantBuffers(cbuffer->GetRegisterIndex(), 1, &buffer);
	if (ShaderUT::IsHS(shaderType))
		m_pDeviceContext->HSSetConstantBuffers(cbuffer->GetRegisterIndex(), 1, &buffer);
	if (ShaderUT::IsCS(shaderType))
		m_pDeviceContext->CSSetConstantBuffers(cbuffer->GetRegisterIndex(), 1, &buffer);
	if (ShaderUT::IsDS(shaderType))
		m_pDeviceContext->DSSetConstantBuffers(cbuffer->GetRegisterIndex(), 1, &buffer);

	if (shaderType == SHADER_TYPE::UNKNOWN_SHADER) {
		//DebugLog("Set CBuffer Error.\n");
		return FALSE;
	}
	return TRUE;
}

bool DeviceContext::SetRasterizerState(RasterizerState* raster) {
	if (m_pDeviceContext == nullptr)
		return false;

	m_pRasterizerState = raster;

	return true;
}

bool DeviceContext::SetDepthStencilState(DepthStencilState*  pDepthStencil) {
	if (m_pDeviceContext == nullptr)
		return false;

	m_pDepthStencilState = pDepthStencil;
	return true;
}


//! Change CBuffer
bool DeviceContext::ChangeCBuffer(CBuffer * cbuffer, void * pData, size_t sz) {
	if (m_pDeviceContext == nullptr)
		return FALSE;

	if (cbuffer == nullptr)
		return FALSE;

	cbuffer->Map(this, pData, sz);

	return true;
}

bool DeviceContext::SetVertexBuffer(VertexBuffer* vb) {
	if (m_pDeviceContext == nullptr)
		return FALSE;

	if (vb == nullptr) {
		//UT::Log("VertexBuffer is null\n");
		return FALSE;
	}

	ID3D11Buffer* buffer = vb->GetBuffer();
	UINT size = vb->GetBufferSize();
	UINT stride = vb->GetStride();
	UINT offset = vb->GetOffset();
	if (buffer == nullptr || size == 0 || stride == 0) {
		//UT::Log("VertexBuffer is null\n");
		return FALSE;
	}

	m_pDeviceContext->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);

	return TRUE;
}
bool DeviceContext::SetIndexBuffer(IndexBuffer*ib) {

	m_pDeviceContext->IASetIndexBuffer(ib->GetBuffer(), DXGI_FORMAT_R32_UINT, 0);

	return TRUE;
}

bool DeviceContext::ApplyRasterizer() {
	if (m_pDeviceContext)
		m_pDeviceContext->RSSetState(m_pRasterizerState->GetRSS());
	return true;
}

bool DeviceContext::ApplyDepthStencil() {
	if (m_pDeviceContext)
		m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState->GetDSS(), 0);
	return true;
}

bool DeviceContext::ClearVertexBuffer() {
	return false;
}
bool DeviceContext::ClearIndexBuffer() {
	return false;
}
bool DeviceContext::ClearCBuffer(int index, SHADER_TYPE type) {
	int count = 1;
	if (index < 0) {
		index = 0;
		count = 16;
	}
	if (index > 15) {
		return false;
	}

	if (type & SHADER_TYPE::VERTEX_SHADER & type)
		m_pDeviceContext->VSSetConstantBuffers(index, count, nullptr);
	if (type & SHADER_TYPE::PIXEL_SHADER & type)
		m_pDeviceContext->PSSetConstantBuffers(index, count, nullptr);
	if (type & SHADER_TYPE::GEOMETRY_SHADER & type)
		m_pDeviceContext->GSSetConstantBuffers(index, count, nullptr);
	if (type & SHADER_TYPE::HULL_SHADER & type)
		m_pDeviceContext->HSSetConstantBuffers(index, count, nullptr);
	if (type & SHADER_TYPE::DOMAIN_SHADER & type)
		m_pDeviceContext->DSSetConstantBuffers(index, count, nullptr);
	if (type & SHADER_TYPE::COMPUTE_SHADER & type)
		m_pDeviceContext->CSSetConstantBuffers(index, count, nullptr);

	return true;
}

/*! =====================================================================================
@brief	
@param	void
@return void
====================================================================================== */
void DeviceContext::UpdateCameraCBuffer() {
	if (m_mainCamera != nullptr) {
		m_mainCamera->UpdateForCBuffer();
	}
}
