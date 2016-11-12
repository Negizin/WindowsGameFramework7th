#include "MeshObject.h"

bool MeshObject::AddGeometry(GeometryObject* pGeometry){
	m_pGeometryArray.push_back(pGeometry);
	return true;
}

int MeshObject::GetGeometryCount(){
	return m_pGeometryArray.size();
}

GeometryObject* MeshObject::GetGeometry(int index){
	return m_pGeometryArray[index];
}