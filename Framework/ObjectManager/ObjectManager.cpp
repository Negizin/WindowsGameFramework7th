#include	"ObjectManager.h"
#include	"../GameObjectClasses/GameObject.h"
#include	"../ComponentClasses/Collider/Collider.h"
#include	"../ComponentClasses/Renderer/Renderer.h"
#include <thread>

/*! =====================================================================================
@brief	�R���X�g���N�^
@param	void
====================================================================================== */
ObjectManager::ObjectManager() {
}

/*! =====================================================================================
@brief	�f�X�g���N�^
@param	void
====================================================================================== */
ObjectManager::~ObjectManager() {
	for (size_t i = 0; i < 4; i++) {
		for (auto itr = m_objectArray[i].begin(); itr != m_objectArray[i].end(); itr++) {
			SafeDelete(*itr);
		}
	}
}

/*! =====================================================================================
@brief	�Q�[���I�u�W�F�N�g�o�^�i�o�^������޼ު�Ă��Ȱ�ެ���ŉ������̂ŁA����`���Ȃ��j
@param	GameObject*
@return void
====================================================================================== */
void	ObjectManager::RegisterObject(GameObject* _pObject) {
	m_objectArray[0].push_back(_pObject);
	ColliderList* _pColliderList = _pObject->GetComponentColliderList();
	for (auto itr = _pColliderList->begin(); itr != _pColliderList->end(); itr++) {

	}
}

/*! =====================================================================================
@brief	�w�肵���X���b�h�E�I�u�W�F�N�g�z��ɃQ�[���I�u�W�F�N�g��o�^����
@param	GameObject*	�o�^����Q�[���I�u�W�F�N�g
@param	unsigned	�o�^��̃X���b�h�E�I�u�W�F�N�g�z��̃C���f�b�N�X(0�`3)
@return void
====================================================================================== */
void ObjectManager::RegisterObject(GameObject * _pObject, unsigned thread) {
	switch (thread) {
		case	0:	m_objectArray[0].push_back(_pObject); return;
		case	1:	m_objectArray[1].push_back(_pObject); return;
		case	2:	m_objectArray[2].push_back(_pObject); return;
		case	3:	m_objectArray[3].push_back(_pObject); return;
		default:	m_objectArray[0].push_back(_pObject); return;
	}
	ColliderList* _pColliderList = _pObject->GetComponentColliderList();
	for (auto itr = _pColliderList->begin(); itr != _pColliderList->end(); itr++) {

	}
}

/*! =====================================================================================
@brief	�e��޼ު�Ĕz��X�V
@param	�O�`�R�̵�޼ު�Ĕz��̃C���f�b�N�X
@return void
====================================================================================== */
void ObjectManager::UpdateThread(unsigned thread) {
	for (unsigned int i = 0; i < m_objectArray[thread].size(); i++) {
		if (m_objectArray[thread][i]->GetActiveFlg()) {
			m_objectArray[thread][i]->Update();
		}
	}
}

/*! =====================================================================================
@brief	�X�V����
@param	void
@return void
====================================================================================== */
void	ObjectManager::Update() {

	//4�X���b�h�ŃI�u�W�F�N�g�z�񖈂ɕ��񏈗�����
	std::thread	_second(&ObjectManager::UpdateThread, this, 1);
	std::thread	_third(&ObjectManager::UpdateThread, this, 2);
	std::thread	_fourth(&ObjectManager::UpdateThread, this, 3);
	UpdateThread(0);

	//�e�X���b�h�̏I���ҋ@
	_second.join();
	_third.join();
	_fourth.join();

	//�Փ˔���

}

/*! =====================================================================================
@brief	�`��p�L���[�ɗL���ȃI�u�W�F�N�g���Z�b�g
@param	void
@return void
====================================================================================== */
void	ObjectManager::RendererUpdate() {
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < m_objectArray[i].size(); j++) {
			//�u�I�u�W�F�N�g���A�N�e�B�u�v����
			//�u�I�u�W�F�N�g��Renderer�R���|�[�l���g�������Ă���v����
			//�uRenderer�R���|�[�l���g���L���v�̏ꍇ�A�`��L���[�ɃZ�b�g����
			if (m_objectArray[i][j]->GetActiveFlg() != false &&
				m_objectArray[i][j]->GetComponentRenderer() != nullptr &&
				m_objectArray[i][j]->GetComponentRenderer()->GetActiveFlg() != false){

			}
		}
	}
}