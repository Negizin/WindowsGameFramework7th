/*!-----------------------------------------------------------------/
//@brief	ClearPass
//
//  ÉNÉäÉAêÍópÉpÉX
//
//@Auther   ã{å¥ïqéj
//@Date     2016/11/02
//-----------------------------------------------------------------*/
#pragma once

#include "RenderPass.h"


class ClearPass :public RenderPass {
public:
	ClearPass();
	virtual ~ClearPass();

	virtual bool Begin(DeviceContext *)override;
	virtual bool Render(DrawQueue * pQueue, DeviceContext *)override;

	virtual bool LoadShaderFromXMLElement(DX11Device *pDev, MyXMLElement *pElm)override;
private:

};

