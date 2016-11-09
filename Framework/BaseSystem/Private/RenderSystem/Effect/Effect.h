//!*******************************************************
//!	Effect.h
//!
//!	Graphics Effect.
//!
#pragma once
#include "../Shader/Shader.h"
#include	"../Utilities/NameObject/NameObject.h"

class DX11Device;
class RasterizerState;
class DepthStencilState;
class Effect :public NameObject {
public:
	//! Constructor
	Effect() : m_vertexShader(nullptr),
		m_pixelShader(nullptr),
		m_geometoryShader(nullptr),
		m_hullShader(nullptr),
		m_domainShader(nullptr),
		m_computeShader(nullptr),
		m_pDepthStencilState(nullptr),
		m_pRasterizerState(nullptr) {
	}

	bool LoadPackageFromXml(DX11Device *pDev, const tstring& file);

	bool	SetVertexShader(VertexShader*);
	bool	SetPixelShader(PixelShader*);
	bool	SetGeometryShader(GeometryShader*);
	bool	SetHullShader(HullShader*);
	bool	SetDomainShader(DomainShader*);
	bool	SetComputeShader(ComputeShader*);

	ID3D11InputLayout*	GetInputLayout();
	VertexShader*		GetVertexShader()const { return m_vertexShader; }
	PixelShader*		GetPixelShader()const { return m_pixelShader; }
	GeometryShader*	GetGeometryShader()const { return m_geometoryShader; }
	HullShader*		GetHullShader()const { return m_hullShader; }
	DomainShader*		GetDomainShader()const { return m_domainShader; }
	ComputeShader*	GetComputeShader()const { return m_computeShader; }

	RasterizerState* GetRasterizerState() { return m_pRasterizerState; }
	DepthStencilState* GetDepthStencilState() { return m_pDepthStencilState; }
protected:
	VertexShader *	m_vertexShader;
	PixelShader *		m_pixelShader;
	GeometryShader*	m_geometoryShader;
	HullShader *		m_hullShader;
	DomainShader *	m_domainShader;
	ComputeShader *	m_computeShader;

	DepthStencilState* m_pDepthStencilState;
	RasterizerState*      m_pRasterizerState;
};