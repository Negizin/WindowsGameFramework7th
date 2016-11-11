#include	"GameObject.h"
#include	"../ComponentClasses/Collider/Collider.h"
#include	"../ComponentClasses/Renderer/Renderer.h"

/*! =====================================================================================
@fn		�R���X�g���N�^
@param	void
====================================================================================== */
GameObject::GameObject() :
	m_isActive(true), m_pCollider(nullptr), m_pRenderer(nullptr) {
	m_transform.Attach(this);
}

/*! =====================================================================================
@fn		�f�X�g���N�^
@param	void
====================================================================================== */
GameObject::~GameObject() {
	SafeDelete(m_pCollider);
	SafeDelete(m_pRenderer);
}

/*! =====================================================================================
@brief	�Փˏ���

�um_isActive �� true�v���um_pCollider �� nullptr�łȂ��v�ꍇ�A�Փ˔��肪�s����B
�Փ˔���ɂ��Փ˂����m���ꂽ�ꍇ�A���̊֐����Ăяo�����B

@param	Collider*�F�ՓˑΏۂ̃R���C�_�[�R���|�[�l���g
@return void
====================================================================================== */
void	GameObject::OnCollision(Collider*	_pOther) {

}

/*! =====================================================================================
@brief	�I�u�W�F�N�g�̍X�V�������s���t���O�̑���(�Z�b�g����Ă���R���|�[�l���g���ꊇ�ő���)
@param	bool�Ftrue���X�VON
====================================================================================== */
void GameObject::Activate(bool _flg) {
	m_isActive = _flg;
	if (m_pCollider != nullptr) { m_pCollider->Activate(_flg); }
	if (m_pRenderer != nullptr) { m_pRenderer->Activate(_flg); }
}

/*! =====================================================================================
@brief	�I�u�W�F�N�g�̏Փ˔�����s���t���O�̑���
@param	bool�Ftrue���Փ�ON
====================================================================================== */
void GameObject::ActivateCollider(bool _flg) {
	if (m_pCollider != nullptr) { m_pCollider->Activate(_flg); }
}

/*! =====================================================================================
@brief	�I�u�W�F�N�g�̕`�揈�����s���t���O�̑���
@param	bool�Ftrue���`��ON
====================================================================================== */
void GameObject::ActivateRenderer(bool _flg) {
	if (m_pRenderer != nullptr) { m_pRenderer->Activate(_flg); }
}

/*! =====================================================================================
@brief	�I�u�W�F�N�g�̍X�V�������s���t���O�̎擾
@param	bool�Ftrue���X�VON
====================================================================================== */
bool GameObject::GetActiveFlg() const {
	return m_isActive;
}

/*! =====================================================================================
@brief	�I�u�W�F�N�g�̃R���C�_�[���擾
@param	bool�Ftrue���X�VON
====================================================================================== */
Collider*	GameObject::GetComponentCollider() const {
	return m_pCollider;
}

/*! =====================================================================================
@brief	�I�u�W�F�N�g�̃����_���[���擾
@param	bool�Ftrue���X�VON
====================================================================================== */
Renderer*	GameObject::GetComponentRenderer() const {
	return m_pRenderer;
}