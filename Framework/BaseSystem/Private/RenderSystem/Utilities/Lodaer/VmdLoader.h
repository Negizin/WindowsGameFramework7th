#pragma once
/**********************************************************************
/*		�C���N���[�h
/*
*********************************************************************/
#include <vector>
#include <list>


#include "../../Math/Bone/MmdBone.h"

/**********************************************************************
/*		���C�u����
/*
*********************************************************************/
using namespace DirectX;
/**********************************************************************
/*		�}�N���A�萔��`
/*
*********************************************************************/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*   CVmdController
*
*   @brief VMD�R���g���[���N���X
*   @author  Miyahara Satoshi
*   \date    2016/5/16�@�V�K�쐬
*
*   \Update
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Vmd
{
public:
#pragma pack(push,1)	//�A���C�������g������I�t
	/*!-----------------------------------------------------------
	//	@struct	VMDHeader
	//	@brief	VMD�\���̃w�b�_
	//	@author	Tatsunori Aoyama
	//	@date	2014/10/03
	------------------------------------------------------------*/
	struct Header
	{
		char vmdHeader[30];
		char vmdModelName[20];
	};

	/*!-----------------------------------------------------------
	//	@struct	VMDMotion
	//	@brief	VMD�\����
	//	@author	Tatsunori Aoyama
	//	@date	2014/10/03
	------------------------------------------------------------*/
	struct Motion
	{
		char			boneName[15];		///< �������{�[���̖��O
		unsigned long	frameNo;			///< �t���[���ԍ�
		float			location[3];		///< �ړ���
		float			localRotation[4];		///< ���f�����[�J�����W�n
		unsigned char	interpolation[64];	///<[4][4][4]���[�V������Ԍ`��
	};

#pragma pack(pop)
};

class VmdLoader{



};


class VmdMotion{
private:
	int time = 0;							// ����
	int MaxFrame = 0;						//���[�V�����ɂ�����t���[��
	int cooltime = 30;
	std::vector<MMDBone>* bones;					//�{�[���z��̃|�C���^
	std::vector<MMDIKBone>* pmdIkData;				//IK�{�[���z��̃|�C���^
	std::vector<Vector4> boneRot;					// ���݂̃{�[���̉�]
	std::vector<Vector3> bonePos;					// ���݂̃{�[���̈ʒu
	std::vector<std::list<KeyFrame>> keyFrames;				// �{�[�����ƂɃL�[�t���[�������X�g�Ƃ��Ă���
	std::vector<std::list<KeyFrame>::iterator> ite_keyFrames;	// �L�[�t���[���̃C�e���[�^

public:
	VmdMotion(void){};//�R���X�g���N�^
	~VmdMotion(){};

	void UpdateBoneMatrix();				// �L�[�t���[���f�[�^�����Ƀ{�[���s����X�V
	void AdvanceTime();
	void Update();
	void SetBonePos(std::vector<Vector3> bonepos);
	void SetBoneRot(std::vector<Vector4> boneros);
	void SetBone(std::vector<MMDBone> &_bone, std::vector<MMDIKBone>& _pmd);
	bool LoadVmdFile(LPCTSTR filename);
private:
	void UpdateIK(const MMDIKBone&);		// IK�{�[���e�����{�[���̍s����X�V

public:
	std::vector<Vector3>* GetBonePos(){ return &bonePos; }
	std::vector<Vector4>* GetBoneRot(){ return &boneRot; }
	std::vector<MMDBone>* GetBone(){ return bones; }
};