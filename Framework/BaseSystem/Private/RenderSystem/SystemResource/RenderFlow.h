//!*******************************************************
//!	RenderFlow.h
//!
//!	The class is renderer manage.
//! Singleton
#pragma once
#include <vector>
#include	"../Utilities/NameObject/NameObject.h"
#include	"../Utilities/XML/Xml.h"

class DeviceContext;
class RenderPass;
class DrawQueue;
class DX11Device;

class RenderFlow :public NameObject {

public:
	virtual	bool	Render(DeviceContext * pDc, DrawQueue *Queue);
	RenderPass*	GetPipeLine(tstring);
	RenderPass*	GetPipeLine(int index);
	int	GetFlowSize();
	bool SetPipeLine(RenderPass * pipeline, int pass = -1);
	bool LoadFlomXML(DX11Device *pDev, const tstring& file);
protected:
	std::vector<RenderPass*> m_renderPass;
};

