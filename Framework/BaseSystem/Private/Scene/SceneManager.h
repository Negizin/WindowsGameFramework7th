/*! =====================================================================================
@file		SceneManager.h
@brief		�V�[���}�l�[�W���[
@author		Takuya Kawakami
@date		2016.03.15	�V�K�쐬
====================================================================================== */
#pragma once
class BaseScene;
class LoadScene;

class SceneManager {
public:
	SceneManager();
	~SceneManager();

	void	Initialize();		//����������
	void	Update();			//�X�V����
	void	SendDrawObject();	//�`�揈��

private:
	BaseScene*	m_pNowScene;	//���ݎ��s���̃V�[��
	BaseScene*	m_pNextScene;	//�V�[���J�ڐ��t�p�X�^�b�N


	bool		m_bNowLoading;	//�V�[���J�ڒ��E���[�f�B���O���t���O
	LoadScene*	m_pLoadScene;	//���[�f�B���O�V�[��

	void	NextSceneLaunch();	//�J�ڐ�V�[���̗����グ
};


