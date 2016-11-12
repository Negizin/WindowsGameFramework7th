#pragma once

#include <Windows.h>
#include <vector>
#include	"../../../../../Utilities/Math/Math.h"

using namespace DirectX;

struct MMDBone {
	int id;						// �{�[��ID�i�ʂ��ԍ��j
	std::string name;			// �{�[����
	unsigned char type;			// �{�[���^�C�v (MMD�̏ꍇ 0:��] 1:��]�ƈړ� 2:IK 3:�s�� 4:IK�e���� 5:��]�e���� 6:IK�ڑ��� 7:��\�� 8:�P�� 9:��]�^�� )
	MMDBone* parent;			// �e�{�[��
	MMDBone* firstChild;		// ��1�q�{�[��
	MMDBone* sibling;			// ���̌Z��{�[��
	Matrix initMat;				// �����p���s��(�{�[�����[�J�����W�n)
	Matrix boneMat;				// �{�[���s��(�{�[�����[�J�����W�n)
	Matrix offsetMat;			// �{�[���I�t�Z�b�g�s��(���f�����[�J�����W�n)

	MMDBone() :type(), id(), parent(), firstChild(), sibling() {	// �R���X�g���N�^
		memcpy(&initMat, &XMMatrixIdentity(), sizeof(XMFLOAT4));
		memcpy(&offsetMat, &XMMatrixIdentity(), sizeof(XMFLOAT4));
		memcpy(&boneMat, &XMMatrixIdentity(), sizeof(XMFLOAT4));
	};

	Matrix GetModelLocalBoneMat();
	Matrix XMGetModelLocalBoneMat();
	Vector4 GetModelLocalPosition();
};


struct MMDIKBone {
	WORD	boneIndex;			///< IK�{�[���ԍ��i�C���f�b�N�X�j
	WORD	effectorBoneIndex;	///< IK�{�[���̈ʒu�ɁA���̃{�[������v������悤��IK�������s����
	BYTE	chainLength;		///< IK�`�F�[���̒���
	WORD	numIterations;		///< �ċA���Z��
	FLOAT	controlWeight;		///< �{�[���̒P�ʐ����p 1.0->4.0[rad]. �܂��u�Ђ��v�Ƃ������O�̃{�[����X�������ɂ��������Ȃ�����������
	std::vector<USHORT>  childBoneIndexVector;	///< �q��IK�̃C���f�b�N�Xvector
};


// �L�[�t���[���A�j���[�V�����f�[�^
struct KeyFrame {
	std::string boneName;		// �{�[����
	unsigned long frameNo;	// �t���[���ԍ�
	Vector3 position;	// �ʒu
	Vector4 rotation;// ��]
	Vector2 interpolation_x[2];	// position.x�̃x�W�F�⊮�p�����[�^
	Vector2 interpolation_y[2];	// position.y�̃x�W�F�⊮�p�����[�^
	Vector2 interpolation_z[2];	// position.z�̃x�W�F�⊮�p�����[�^
	Vector2 interpolation_r[2];	// rotation�̃x�W�F�⊮�p�����[�^
	bool operator < (const KeyFrame &k) const {	// �t���[���ԍ��Ń\�[�g���邽�߂̔�r���Z�q
		return frameNo < k.frameNo;
	}
};
