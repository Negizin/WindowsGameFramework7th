/*!-----------------------------------------------------------------/
//@brief	IKBone.h
//
//  IK�{�[���N���X
//
//@Auther   �{���q�j
//@Date     2016/10/30
//-----------------------------------------------------------------*/
#pragma once

#include	"../Bone/Bone.h"
#include	<Windows.h>
#include	<vector>


struct IKBone {
	WORD	boneIndex;			///< IK�{�[���ԍ��i�C���f�b�N�X�j
	WORD	effectorBoneIndex;	///< IK�{�[���̈ʒu�ɁA���̃{�[������v������悤��IK�������s����
	BYTE	chainLength;		///< IK�`�F�[���̒���
	WORD	numIterations;		///< �ċA���Z��
	FLOAT	controlWeight;		///< �{�[���̒P�ʐ����p 1.0->4.0[rad]. �܂��u�Ђ��v�Ƃ������O�̃{�[����X�������ɂ��������Ȃ�����������
	std::vector<USHORT>  childBoneIndexVector;	///< �q��IK�̃C���f�b�N�Xvector
};