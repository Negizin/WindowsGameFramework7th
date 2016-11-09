//!*******************************************************
//!	DrawQueue.h
//!
//!	RenderQueue. the class is geomtry list.
//!

#pragma once
#include	<d3d11.h>
#include	"../Utilities/NameObject/NameObject.h"
#include	"../Utilities/Interface/IStaticNameObjectList.h"
#include "../DrawObject/DrawObject.h"
#include	<vector>


class DrawQueue :public NameObject, public IStaticNameObjectList<DrawQueue> {
public:
	DrawQueue();
	virtual ~DrawQueue();

	bool Add(DrawObject*);
	DrawObject* Find(tstring name);
	DrawObject* Find(int Index);
	bool Remove(DrawObject*);

	bool Begin(DeviceContext * pDc,
		bool zEnable,
		bool zWriteEnable,
		D3D11_CULL_MODE cullMopde);

	bool End();

	bool Render(DeviceContext*);

private:
	DrawQueue(const DrawQueue&) = delete;
	DrawQueue& operator = (const DrawQueue&) = delete;
	std::vector<DrawObject*> m_drawObjList;
};