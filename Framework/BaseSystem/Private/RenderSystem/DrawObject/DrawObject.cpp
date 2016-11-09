#include	"DrawObject.h"
#include	"../../../../Utilities/Math/Matrix/Matrix.h"

bool DrawObject::Create(Device* pDev) {
	(void) pDev;
	return false;
}

bool DrawObject::Draw(DeviceContext* context) {
	(void) context;
	return false;
}
bool DrawObject::UpdateTransform(DeviceContext* context) {
	(void) context;
	return false;
}
bool DrawObject::UpdateMaterial(DeviceContext* context) {
	(void) context;
	return false;
}
bool DrawObject::UpdateIndexBuffer(DeviceContext* context) {
	(void) context;
	return false;
}
bool DrawObject::UpdateVertexBuffer(DeviceContext* context) {
	(void) context;
	return false;
}
bool DrawObject::ApplyVertexBuffer(DeviceContext* context) {
	(void) context;
	return false;
}
bool DrawObject::ApplyTransForm(DeviceContext* context) {
	(void) context;
	return false;
}
bool DrawObject::ApplyIndexBuffer(DeviceContext* context) {
	(void) context;
	return false;
}
bool DrawObject::ApplyMaterial(DeviceContext* context) {
	(void) context;
	return false;
}

Matrix DrawObject::GetWorldMatrix() {
	return Matrix::identity;
}

Matrix DrawObject::GetLocalMatrix() {
	return Matrix::identity;
}