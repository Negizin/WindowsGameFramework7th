#include "MMDSkeleton.h"

bool MMDSkeleton::AddIKBone(int index, int length, float weight, int effbone, int numItr) {
	IKBone *ikBone = new IKBone();
	ikBone->boneIndex = index;
	ikBone->chainLength = length;
	ikBone->controlWeight = weight;
	ikBone->effectorBoneIndex = effbone;
	ikBone->numIterations = numItr;

	m_pIKboneArray.push_back(ikBone);
	return true;
}

bool MMDSkeleton::AddIKChild(int index, int childindex) {
	if (m_pIKboneArray.size() < index - 1)return false;

	m_pIKboneArray[index]->childBoneIndexVector.push_back(childindex);
	return true;
}

bool MMDSkeleton::UpdateSkeleton() {
	Skeleton::UpdateSkeleton();

	for (unsigned int i = 0; i < m_pIKboneArray.size(); ++i) {
		UpdateIK(m_pIKboneArray[i]);
	}
	return true;
}

bool MMDSkeleton::UpdateIK(const IKBone* ikData) {
	Vector3 LocalEffectorPos, localTargetPos;
	for (unsigned int j = 0; j < ikData->numIterations; ++j) {
		//�qIK�̕���
		for (unsigned int i = 0; i < ikData->childBoneIndexVector.size(); ++i) {
			// �qIK�̃C���f�b�N�X
			unsigned short attentionIdx = ikData->childBoneIndexVector[i];
			// �G�t�F�N�^�̈ʒu
			Vector3 effectorPos = m_pboneArray[ikData->effectorBoneIndex]->GetTransform()->GetLocalPosition();

			// �^�[�Q�b�g�̈ʒu
			Vector3 targetPos = m_pboneArray[ikData->boneIndex]->GetTransform()->GetLocalPosition();

			//���[���h���W���璍�ڃm�[�h�ւ̋Ǐ����W�֕ϊ�
			Matrix InvCoord = XMMatrixInverse(&XMMatrixDeterminant(
				m_pboneArray[attentionIdx]->GetTransform()->ToLocalMatrix().ToXMMATRIX()),
				m_pboneArray[attentionIdx]->GetTransform()->ToLocalMatrix().ToXMMATRIX());

			LocalEffectorPos = effectorPos.TransformCood(InvCoord);
			localTargetPos = targetPos.TransformCood(InvCoord);

			// �G�t�F�N�^�̃��[�J�������i���ڃ{�[���̈ʒu��j
			Vector3 localEffectorDir = LocalEffectorPos.Normalized();
			// �^�[�Q�b�g�̃��[�J�������i���ڃ{�[���̈ʒu��j
			Vector3 localTargetDir = localTargetPos.Normalized();

			if (m_pboneArray[attentionIdx]->GetName().find(_T("�Ђ�")) != std::string::npos) {
				localEffectorDir.x = 0;
				localEffectorDir = localEffectorDir.Normalized();
				localTargetDir.x = 0;
				localTargetDir = localTargetDir.Normalized();
			}

			float p = Vector3::Dot(localEffectorDir, localTargetDir);
			if (p > 1.0f)p = 1.0f;
			if (p < 0.0f)p = 0.0f;

			float angle = acos(p);
			if (angle > 1.0f) angle = 0.9f;
			if (angle > 0.004)	// �v�Z�덷�ɂ��1���z�����acos()�����U����̂Œ���!
			{
				if (angle > 4.0f * ikData->controlWeight) angle = 2.0f*ikData->controlWeight;
				Vector3 axis = Vector3::Cross(localEffectorDir, localTargetDir).Normalized();
				if (axis.Length() > 0.02f) {
					Quaternion quat = Quaternion::AngleAxis(axis, angle);
					Matrix rotaion = quat.ToMatrix();

				}

			}
		}
	}
	return true;
}