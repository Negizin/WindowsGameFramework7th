/*!-----------------------------------------------------------------/
//@brief	RenderPass
//
//  レンダーパスクラス
//
//@Auther   宮原敏史
//@Date     2016/9/25
//@Update	2016/11/01	XMLの読み込みを追加
　　　　　　　　　　　　DrawQueueの分離
//-----------------------------------------------------------------*/
#pragma once
#pragma once
#include	<d3d11.h>
#include	"../DX11Device/DeviceContext.h"
#include	"../Utilities/NameObject/NameObject.h"
#include	"../Utilities/XML/Xml.h"

class Effect;
class DrawQueue;
class RenderTarget;
class RasterizerState;



class RenderPass :public NameObject {
public:
	RenderPass();
	virtual ~RenderPass();

	virtual bool Begin(DeviceContext*);
	virtual bool Render(DrawQueue *, DeviceContext*);
	virtual bool End(DeviceContext*);
	virtual bool SetShader(Effect*);
	virtual bool SetInputSlot(int index, Texture*);
	virtual bool SetOutputSlot(int index, RenderTarget * rtv);
	virtual Texture* GetInputSlot(int index);
	virtual RenderTarget* GetOutputSlot(int index = 0);
	virtual bool SetDepthSlot(DepthStencil *pDepth);
	virtual bool LoadShaderFromXMLElement(DX11Device* pDev, MyXMLElement * pElement);
	virtual bool LoadIOSlotFromXMLElement(DX11Device* pDev, MyXMLElement * pElement);
protected:
	bool ApplyRTV(DeviceContext *pDC);
protected:

	Texture* m_pInputSlot[DeviceContext::MAX_RTs];
	RenderTarget* m_pOutputSlot[DeviceContext::MAX_RTs];
	DepthStencil* m_pDepthStencil;
	Effect* m_pShader;
	RasterizerState* m_pRasterizerState;
	DepthStencilState* m_pDepthStencilState;
};