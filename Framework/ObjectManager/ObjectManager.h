/*! =====================================================================================
@file		ObjectManager.h
@brief		�I�u�W�F�N�g�}�l�[�W���[
@author		Takuya Kawakami
@date		2015.12.15	�V�K�쐬
====================================================================================== */
#pragma once
#include	<vector>
#include	<list>
class GameObject;

class ObjectManager {
public:
	ObjectManager();
	~ObjectManager();

	/*! =====================================================================================
	@brief	�Q�[���I�u�W�F�N�g�o�^
	@param	GameObject*
	@return void
	====================================================================================== */
	void	RegisterObject(GameObject*	setObject);

	/*! =====================================================================================
	@brief	�w�肵���X���b�h�E�I�u�W�F�N�g�z��ɃQ�[���I�u�W�F�N�g��o�^����
	@param	GameObject*	�o�^����Q�[���I�u�W�F�N�g
	@param	unsigned	�o�^��̃X���b�h�E�I�u�W�F�N�g�z��̃C���f�b�N�X(0�`3)
	@return void
	====================================================================================== */
	void	RegisterObject(GameObject*	setObject, unsigned thread);

	void	Update();			//�X�V����
	void	RendererUpdate();	//�`��p�L���[�ɗL���ȵ�޼ު�Ă��Z�b�g

private:
	//Data
	std::vector<GameObject*>	m_objectArray[4];

	//Method
	void	UpdateThread(unsigned	thread);

};