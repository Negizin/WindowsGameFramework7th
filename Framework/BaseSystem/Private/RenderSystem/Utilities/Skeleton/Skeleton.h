/*!-----------------------------------------------------------------/
//@brief	Skeleton
//
//  ƒXƒPƒ‹ƒgƒ“ƒNƒ‰ƒX
//
//@Auther   ‹{Œ´•qŽj
//@Date     2016/10/30
//-----------------------------------------------------------------*/
#pragma once
#include <vector>
#include	"../NameObject/NameObject.h"
#include	"../../../../../Utilities/Math/Math.h"
#include	"../../../../../ComponentClasses/Transform/Transform.h"

class Bone;
class Skeleton :public NameObject {
public:
	Skeleton();
	virtual ~Skeleton();
	bool AddBone(Transform* pTransform,
		int boneID,
		const Matrix& bindPoseMatrix,
		Transform* pRootBone);

	bool isUpdate() { return m_isUpdate; }
	bool ToExecutableState() { m_isUpdate = false; return true; };
	virtual bool UpdateSkeleton();
	std::vector<Bone *>& GetBoneArray();
protected:
	bool m_isUpdate;
	std::vector<Bone *> m_pboneArray;
};

