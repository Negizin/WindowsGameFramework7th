#include	"Buffer.h"
#include	"../DX11Device/DX11Device.h"
#include	"../DX11Device/DeviceContext.h"

//! Create Buffer
bool	Buffer::CreateBuffer(__in DX11Device *dev,
	__in void * pData,
	__in size_t size,
	__in UINT cpuAct,
	__in UINT type) {

	HRESULT hr = E_FAIL;

	// バッファー リソース。
	D3D11_BUFFER_DESC BufferDesc;

	// サブリソース
	D3D11_SUBRESOURCE_DATA resource;

	D3D11_USAGE Usage = D3D11_USAGE_DEFAULT;

	if (cpuAct)
		Usage = D3D11_USAGE_DYNAMIC;
	else
		Usage = D3D11_USAGE_DEFAULT;

	if (pData) {
		resource.pSysMem = pData;
		resource.SysMemPitch = 0;
		resource.SysMemSlicePitch = 0;
	}

	// バッファの設定
	::ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.ByteWidth = size;                  // バッファサイズ
	BufferDesc.Usage = Usage;                     // リソース使用法を特定する
	BufferDesc.BindFlags = type;                  // バッファの種類
	BufferDesc.CPUAccessFlags = cpuAct;           // CPU アクセス
	BufferDesc.MiscFlags = 0;                     // その他のフラグも設定しない


	// バッファを作成する
	hr = dev->GetDevD3D()->CreateBuffer(&BufferDesc, &resource, &m_buffer);

	if (FAILED(hr)) {
		return FALSE;
	}

	return TRUE;
}

//!	Map
bool Buffer::Map(__in DeviceContext *dev,
	__in void *pData,
	__in size_t size) {
	if (dev->GetDeviceContext() == nullptr)
		return false;

	if (m_buffer == nullptr)
		return false;

	ID3D11DeviceContext* context = dev->GetDeviceContext();

	D3D11_MAPPED_SUBRESOURCE mappedResource;

	context->Map(m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	CopyMemory(mappedResource.pData, pData, size);

	context->Unmap(m_buffer, 0);

	return true;
}