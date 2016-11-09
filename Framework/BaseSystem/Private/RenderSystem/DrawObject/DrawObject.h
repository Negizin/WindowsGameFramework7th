//!*******************************************************
//!	DrawObject.h
//!
//!	The class has a draw call.
//!
#pragma once
#include	"../../../Public/Common/Common.h"
#include	"../Utilities/NameObject/NameObject.h"

class Device;
class DeviceContext;
class Matrix;

class DrawObject : public NameObject {
public:
	virtual bool Create(Device*);
	virtual bool Draw(DeviceContext*);

	virtual bool UpdateTransform(DeviceContext* context);
	virtual bool UpdateMaterial(DeviceContext* context);
	virtual bool UpdateIndexBuffer(DeviceContext* context);
	virtual bool UpdateVertexBuffer(DeviceContext* context);

	virtual bool ApplyTransForm(DeviceContext * context);
	virtual bool ApplyMaterial(DeviceContext* context);
	virtual bool ApplyIndexBuffer(DeviceContext* context);
	virtual bool ApplyVertexBuffer(DeviceContext* context);

	virtual Matrix GetWorldMatrix();
	virtual Matrix GetLocalMatrix();
};