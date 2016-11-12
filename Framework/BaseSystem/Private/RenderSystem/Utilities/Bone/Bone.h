/*!-----------------------------------------------------------------/
//@brief	Bone.h
//
//  É{Å[ÉìÉNÉâÉX
//
//@Auther   ã{å¥ïqéj
//@Date     2016/10/30
//-----------------------------------------------------------------*/
#pragma once

#include "../NameObject/NameObject.h"
#include	"../../../../../Utilities/Math/Matrix/Matrix.h"
class Transform;

class Bone :public NameObject {
	friend class Skeleton;
public:
	Bone();
	~Bone();

	int GetBoneID();
	Transform *GetTransform();
	const Matrix& GetBoneMatrix();
	bool ComputeBoneMatrix();
	bool SetTransForm(Transform * pTransform);
	bool SetBindPoseMatrix(const Matrix& bindPoseMatrix);
	bool SetBoneID(int boneID);
protected:
	Transform *m_pRootBone;
	Transform *m_pTransform;
	int			m_boneID;
	Matrix		m_bindPoseMatrix;
	Matrix		m_invBindPoseMatrix;
	Matrix		m_boneMatrix;
};

