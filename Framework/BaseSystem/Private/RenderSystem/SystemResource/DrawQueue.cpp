#include "DrawQueue.h"

// Static List �̍쐬
INSTANTIATE_NAME_OBJ_LIST(DrawQueue)

DrawQueue::DrawQueue() {
	m_drawObjList.reserve(512);
}

DrawQueue::~DrawQueue() {
	m_drawObjList.clear();
}

bool DrawQueue::Add(DrawObject* obj) {
	if (obj == nullptr)
		return FALSE;
	m_drawObjList.push_back(obj);

	return TRUE;
}
DrawObject* DrawQueue::Find(tstring name) {
	HASH hash = UT::StringToHash(name);
	for (auto it : m_drawObjList)
		if (hash == it->GetHashCode())
			return it;
	//DebugLog("Find Fail\n");
	return nullptr;
}

DrawObject* DrawQueue::Find(int Index) {
	if (m_drawObjList.size() > (unsigned) Index)
		return m_drawObjList[Index];
	else
		return nullptr;
}
bool DrawQueue::Remove(DrawObject * obj) {
	for (auto it = m_drawObjList.begin(); it != m_drawObjList.end(); ++it) {
		if (obj == *it) {
			m_drawObjList.erase(it);
			return TRUE;
		}
	}
	//DebugLog("Remove Fail\n");
	return FALSE;
}

bool DrawQueue::Begin(DeviceContext * pDc,
	bool zEnable,
	bool zWriteEnable,
	D3D11_CULL_MODE cullMopde) {
	//todo dc set data
	(void) zEnable;
	(void) zWriteEnable;
	(void) cullMopde;

	return TRUE;
}

bool DrawQueue::End() {
	//todo
	return TRUE;
}

bool DrawQueue::Render(DeviceContext* pDc) {
	for each (auto var in m_drawObjList) {
		var->UpdateIndexBuffer(pDc);
		var->UpdateVertexBuffer(pDc);
		var->UpdateMaterial(pDc);
		var->UpdateTransform(pDc);

		var->ApplyIndexBuffer(pDc);
		var->ApplyVertexBuffer(pDc);
		var->ApplyMaterial(pDc);
		var->ApplyTransForm(pDc);
		var->Draw(pDc);
	}
	return TRUE;
}