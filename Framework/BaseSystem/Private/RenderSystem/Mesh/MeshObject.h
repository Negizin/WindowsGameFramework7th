/*!-----------------------------------------------------------------/
//@brief	MeshObject.h
//
//  Load‚µ‚½Mesh‚ð•Û‘¶‚µ‚Ä‚¨‚­‚½‚ß‚ÌƒRƒ“ƒeƒi
//
//@Auther   ‹{Œ´•qŽj
//@Date     2016/11/08
//-----------------------------------------------------------------*/
#pragma once

#include	"../Utilities/NameObject/NameObject.h"
#include	"../DrawObject/GeometryObject.h"
#include <vector>
//class GeometryObject;
class Skeleton;
class MeshObject :public NameObject {

public:
	bool AddGeometry(GeometryObject *pGeometory);
	GeometryObject * GetGeometry(int index);
	int GetGeometryCount();
	Skeleton*	GetSkeleton() { return m_pSkeleton; }
	bool SetSkeleton(Skeleton* pSkeleton) {
		m_pSkeleton = pSkeleton;
		return true;
	}
private:
	Skeleton *m_pSkeleton;
	std::vector<GeometryObject *> m_pGeometryArray;
};