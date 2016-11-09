#ifdef SHADER_INC //インクルードされていなければ無視する

#include <d3dcompiler.h>
#include <vector>
#include	"../../Common/SafeFunction.h"
#include	"../Utilities/File/File.h"

template<typename T>
bool Shader<T>::CompileFromFile(
	__in ID3D11Device* pDev,
	__in const char* filename,
	__in const char*  entryPoint,
	__in const char*  pProfile) {
	ID3D10Blob* pBlob = nullptr;
	ID3D10Blob* error = nullptr;

	// 行列を列優先で設定し、古い形式の記述を許可しないようにする
	UINT Flag1 = D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR | D3D10_SHADER_ENABLE_STRICTNESS;
	// 最適化レベルを設定する
#if defined(DEBUG) || defined(_DEBUG)
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL0;
#else
	Flag1 |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#endif

	// ファイルを元にエフェクトをコンパイルする
	D3DCompileFromFile(filename,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint,
		pProfile,
		Flag1,
		0,
		&pBlob,
		&error);

	if (error) {
		return FALSE;
	}

	if (pBlob == nullptr) {
		return FALSE;
	}


	m_size = pBlob->GetBufferSize();
	m_bin = new unsigned char[m_size];
	CopyMemory(m_bin, pBlob->GetBufferPointer(), m_size);
	SafeRelease(pBlob);

	CompileFromMemory(pDev, m_bin, m_size);
	if (!isSuccess)
		return TS_FALSE;

	//DebugLog( "Load Success -> \"%s\"\n" , filename );

	tstring name;
	name = UT::PassToFileName(filename);
	name = name.substr(0, name.rfind('.'));
	SetName(name);
	AddObject(this);
	return TRUE;
};


template<typename T>
bool Shader<T>::LoadFromCSO(ID3D11Device* pd3dDevice, const TCHAR* filename) {
	if (pd3dDevice == nullptr)
		return FALSE;

	bool isSuccess = Load(filename);

	if (!isSuccess)
		return FALSE;

	isSuccess = CompileFromMemory(pd3dDevice, m_bin, m_size);

	if (!isSuccess)
		return FALSE;


	tstring name;
	name = UT::PassToFileName(filename);
	name = name.substr(0, name.rfind('.'));
	SetName(name);
	//AddObject(this);
	return TRUE;
}


template<>
bool VertexShader::CompileFromMemory(ID3D11Device* pDev, void* memory, size_t sz) {
	if (pDev == nullptr) return FALSE;
	HRESULT hr = pDev->CreateVertexShader(memory, sz, nullptr, &m_shader);
	if (FAILED(hr))return FALSE;
	if (CreateInputLayout(pDev) == FALSE)
		return FALSE;
	return TRUE;
}

template<>
bool PixelShader::CompileFromMemory(ID3D11Device* pDev, void* memory, size_t sz) {
	if (pDev == nullptr) return FALSE;
	HRESULT hr = pDev->CreatePixelShader(memory, sz, nullptr, &m_shader);
	if (FAILED(hr))return FALSE;
	return TRUE;
}
template<>
bool HullShader::CompileFromMemory(ID3D11Device* pDev, void* memory, size_t sz) {
	if (pDev == nullptr) return FALSE;
	HRESULT hr = pDev->CreateHullShader(memory, sz, nullptr, &m_shader);
	if (FAILED(hr))return FALSE;
	return TRUE;
}
template<>
bool GeometryShader::CompileFromMemory(ID3D11Device* pDev, void* memory, size_t sz) {
	if (pDev == nullptr) return FALSE;
	HRESULT hr = pDev->CreateGeometryShader(memory, sz, nullptr, &m_shader);
	if (FAILED(hr))return FALSE;
	return TRUE;
}
template<>
bool ComputeShader::CompileFromMemory(ID3D11Device* pDev, void* memory, size_t sz) {
	if (pDev == nullptr) return FALSE;
	HRESULT hr = pDev->CreateComputeShader(memory, sz, nullptr, &m_shader);
	if (FAILED(hr))return FALSE;
	return TRUE;
}
template<>
bool DomainShader::CompileFromMemory(ID3D11Device* pDev, void* memory, size_t sz) {
	if (pDev == nullptr) return FALSE;
	HRESULT hr = pDev->CreateDomainShader(memory, sz, nullptr, &m_shader);
	if (FAILED(hr))return FALSE;
	return TRUE;
};

//======================================================
//! Create Auto Input Layout 
//======================================================
template<>
bool VertexShader::CreateInputLayout(ID3D11Device* pDev) {
	//======================================================
	//! step01 コンパイル済み頂点シェーダからメタデータの取得
	//======================================================
	ID3D11ShaderReflection* pVertexShaderReflection = nullptr;
	if (FAILED(D3DReflect(m_bin,
		m_size,
		IID_ID3D11ShaderReflection,
		(void**) &pVertexShaderReflection))) {
		return FALSE;
	}

	//======================================================
	//! step02 メタデータからDescを取得
	//======================================================
	D3D11_SHADER_DESC shaderDesc;
	pVertexShaderReflection->GetDesc(&shaderDesc);

	//======================================================
	//! step03 DescからInputLayoutを生成するためのデータを構築
	//======================================================
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	for (UINT i = 0; i < shaderDesc.InputParameters; i++) {
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		//switch - case 見やすくするため省略
		enum {
			F32 = D3D_REGISTER_COMPONENT_FLOAT32,
			S32 = D3D_REGISTER_COMPONENT_SINT32,
			U32 = D3D_REGISTER_COMPONENT_UINT32,
		};
		//1Dデータ
		if (paramDesc.Mask == 1) {
			switch (paramDesc.ComponentType) {
				case U32:elementDesc.Format = DXGI_FORMAT_R32_UINT; break;
				case S32:elementDesc.Format = DXGI_FORMAT_R32_SINT; break;
				case F32:elementDesc.Format = DXGI_FORMAT_R32_FLOAT; break;
			}
		}
		//2Dデータ
		else if (paramDesc.Mask <= 3) {
			switch (paramDesc.ComponentType) {
				case U32:elementDesc.Format = DXGI_FORMAT_R32G32_UINT; break;
				case S32:elementDesc.Format = DXGI_FORMAT_R32G32_SINT; break;
				case F32:elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT; break;
			}
		}
		//3Dデータ
		else if (paramDesc.Mask <= 7) {
			switch (paramDesc.ComponentType) {
				case U32:elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT; break;
				case S32:elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT; break;
				case F32:elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT; break;
			}
		}
		//4Dデータ
		else if (paramDesc.Mask <= 15) {
			switch (paramDesc.ComponentType) {
				case U32:elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT; break;
				case S32:elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT; break;
				case F32:elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; break;
			}
		}

		inputLayoutDesc.push_back(elementDesc);
	}

	//======================================================
	//! step04 DescからInputLayoutを構築
	//======================================================
	HRESULT hr = pDev->CreateInputLayout(&inputLayoutDesc[0],
		inputLayoutDesc.size(),
		m_bin,
		m_size,
		&m_inputLayout);

	SafeRelease(pVertexShaderReflection);
	if (FAILED(hr)) {

		return FALSE;
	}
	return TRUE;
};
#endif