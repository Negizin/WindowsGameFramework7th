/*!-----------------------------------------------------------------/
//@brief	MMDSkeleton.h
//
//  MMD専用のスケルトンクラス
//
//@Auther   宮原敏史
//@Date     2016/11/08
//-----------------------------------------------------------------*/
#pragma once
#include "Skeleton.h"
#include "../IKBone/IKBone.h"

class MMDSkeleton :public Skeleton {
public:
	bool AddIKBone(int index, int length, float weight, int effbone, int numItr);
	bool AddIKChild(int index, int childindex);
	virtual bool UpdateSkeleton();
protected:
	bool UpdateIK(const IKBone* ikData);
	std::vector<IKBone *> m_pIKboneArray;
};
