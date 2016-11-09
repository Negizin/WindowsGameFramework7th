#include "ClearPass.h"

ClearPass::ClearPass() :RenderPass() {
}

ClearPass::~ClearPass() {
}

bool ClearPass::Begin(DeviceContext *pDC) {
	ApplyRTV(pDC);

	return true;
}

bool ClearPass::Render(DrawQueue *pQue, DeviceContext*pDC) {
	(void) pQue;
	pDC->Clear();

	return true;
}

bool ClearPass::LoadShaderFromXMLElement(DX11Device *pDev, MyXMLElement *pElm) {
	(void) pDev;
	(void) pElm;
	return true;
}
