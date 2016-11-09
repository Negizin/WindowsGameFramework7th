//!*******************************************************
//!	Shader.h
//!
//!	Shader Template
//!

#pragma once

//inlファイル用のインクルードガード
#ifndef SHADER_INC
#define SHADER_INC

//include
#include	<d3d11.h>
#include	"../Utilities/BinaryUT/Binary.h"
#include	"../Utilities/Interface/IStaticNameObjectList.h"

#pragma comment (lib,"d3d11.lib")

template<typename Shadertype>
class Shader : public Binary, public IStaticNameObjectList<Shader<Shadertype>> {
public:
	Shader() :m_shader(nullptr), m_inputLayout(nullptr) {
		this->Binary::Binary();
	}

	inline bool CompileFromFile(__in ID3D11Device* pDev,
		__in const char* filename,
		__in const char* entryPoint,
		__in const char* pProfile);

	inline bool LoadFromCSO(__in ID3D11Device * pDev,
		__in const TCHAR* filename);

	inline bool CompileFromMemory(ID3D11Device* pDev,
		void* memory,
		size_t size);

	inline bool CreateInputLayout(ID3D11Device* pDev);

	ID3D11InputLayout* GetInputLayout()const { return m_inputLayout; }
	Shadertype* GetShader()const { return m_shader; }

	virtual ~Shader() {
		SafeRelease(m_shader);
		SafeRelease(m_inputLayout);
	};
protected:
	Shadertype*				m_shader;
	ID3D11InputLayout*	m_inputLayout;
};

typedef Shader<ID3D11VertexShader>	VertexShader;
typedef Shader<ID3D11PixelShader>		PixelShader;
typedef Shader<ID3D11GeometryShader>	GeometryShader;
typedef Shader<ID3D11HullShader>		HullShader;
typedef Shader<ID3D11DomainShader>	DomainShader;
typedef Shader<ID3D11ComputeShader>	ComputeShader;

#include "Shader.inl"

#endif