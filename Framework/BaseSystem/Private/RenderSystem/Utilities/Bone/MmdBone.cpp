#include "MmdBone.h"

Matrix MMDBone::GetModelLocalBoneMat(){
	if (parent)
	{
		XMMATRIX workBone = XMLoadFloat4x4(&boneMat);
		XMMATRIX workLocalBone = XMLoadFloat4x4(&parent->GetModelLocalBoneMat());

		Matrix out;
		XMStoreFloat4x4(&out, workBone*workLocalBone);
		return out;
	}
	else return boneMat;
}

Matrix MMDBone::XMGetModelLocalBoneMat() {				// ���f�����[�J�����W�n�ł̃{�[���s����擾
	if (parent)
	{
		Matrix workBone = XMLoadFloat4x4(&boneMat);
		Matrix workLocalBone = XMLoadFloat4x4(&parent->GetModelLocalBoneMat());
		return  workBone*workLocalBone;
	}
	else return XMLoadFloat4x4(&boneMat);
}

Vector4 MMDBone::GetModelLocalPosition()
{		// ���f�����[�J�����W�n�ł̃{�[���ʒu���擾
	XMVECTOR v = XMVectorSet(0, 0, 0, 0);
	XMFLOAT4 out;
	v = XMVector3TransformCoord(v, XMGetModelLocalBoneMat().ToXMMATRIX());
	XMStoreFloat4(&out, v);
	return out;
}