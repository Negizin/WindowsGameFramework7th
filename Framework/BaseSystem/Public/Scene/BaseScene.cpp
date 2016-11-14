#include	"BaseScene.h"
#include	"../../../GameObjectClasses/2D/FadeSprite.h"
#include	"../../Private/RenderSystem/SystemResource/DrawQueue.h"

/*! =====================================================================================
@brief	�R���X�g���N�^

	!! �R���X�g���N�^�͌p����ł��Œ���̏����ɗ}���Ă��������B
	!! ���[�h�ɃR�X�g��v������͕̂��񏈗������Initialize()�Ɏ�������悤�ɂ��Ă��������B

@param	void
====================================================================================== */
BaseScene::BaseScene() {
	m_pFadeSprite = new FadeSprite();
	m_objectManager.RegisterObject(m_pFadeSprite);
	m_nextSceneID = 0;

	m_pQueue = new DrawQueue();
}

/*! =====================================================================================
@brief	�f�X�g���N�^
@param	void
====================================================================================== */
BaseScene::~BaseScene() {
	SafeDelete(m_pQueue);
}

/*! =====================================================================================
@brief	�X�V����
@param	void
@return void
====================================================================================== */
BaseScene * BaseScene::Update() {

	//�S��޼ު�Ă̍X�V����
	m_objectManager.Update();

	//�V�[���J�ڔ���
	if (CheckSceneTransition() == true) {
		m_pFadeSprite->StartFadeOut();	//�t�F�[�h�A�E�g�J�n
	}

	//�V�[���J�ڒ�
	if (m_nextSceneID != 0) {
		//�t�F�[�h�A�E�g������
		if (m_pFadeSprite->GetFadingState() == false) {
			//�J�ڐ�V�[���̃|�C���^��Ԃ�
			switch (m_nextSceneID) {
				case	1:	return this;
				case	2:	return this;
				case	3:	return this;
				default: MessageBox(NULL, _T("Update() return value is invalid"), _T("Error:BaseScene.cpp"), MB_OK); return this;
			}
		}
	}
	return	this;	//�V�[���J�ڂȂ�
}


/*! =====================================================================================
@brief	�`��O����
@param	void
@return void
====================================================================================== */
void BaseScene::UpdateRenderer() {
	m_objectManager.RendererUpdate();
}

/*! =====================================================================================
@brief	�V�[���J�ڂ̏�������
@param	void
@return bool	�V�[���J�ڂ���Ftrue
====================================================================================== */
bool BaseScene::CheckSceneTransition() {

	/* ������F�p����ŏ��������������Ă������� */

	//�V�[���J�n�E�I�����̃t�F�[�h���̓V�[���J�ڂ��󂯕t���Ȃ�
	if (m_pFadeSprite->GetFadingState() == true || m_nextSceneID != 0) {
		return false;
	}

	//�V�[���J�ڏ���
	if (false) {
		m_nextSceneID = 1;
		return true;
	}
	else if (false) {
		m_nextSceneID = 2;
		return true;
	}
	else {
		m_nextSceneID = 3;
		return true;
	}

	//�V�[���J�ڂȂ�
	return	false;
}
