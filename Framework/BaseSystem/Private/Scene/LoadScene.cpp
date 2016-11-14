#include	"LoadScene.h"
#include	<thread>

/*! =====================================================================================
@brief	�R���X�g���N�^
@param	void
====================================================================================== */
LoadScene::LoadScene() {
	m_pNextScene = nullptr;
}

/*! =====================================================================================
@brief	�R���X�g���N�^
@param	bool*	���[�h�X���b�h�Ǘ��p�t���O�ւ̃|�C���^
====================================================================================== */
LoadScene::LoadScene(bool * _pSyncFlg) {
	m_pNextScene = nullptr;
	m_pLoadingFlg = _pSyncFlg;
}

/*! =====================================================================================
@brief	�f�X�g���N�^
@param	void
====================================================================================== */
LoadScene::~LoadScene() {
}

/*! =====================================================================================
@brief	����������
@param	void
@return void
====================================================================================== */
void LoadScene::Initialize() {
}

/*! =====================================================================================
@brief	����������
@param	BaseScene*�F�J�ڐ�V�[��
@return void
====================================================================================== */
void LoadScene::Initialize(BaseScene * _pNextScene) {
	m_pNextScene = _pNextScene;
	std::thread	_loadThread(&LoadScene::Loading, this);	//�ʃX���b�h�őJ�ڐ�̃V�[��������������
	_loadThread.detach();
}

/*! =====================================================================================
@brief	�X�V����
@param	void
@return BaseScene*�F�J�ڐ�V�[���̃|�C���^�i�J�ڂȂ���this�|�C���^��Ԃ��j
====================================================================================== */
BaseScene * LoadScene::Update() {

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
			return m_pNextScene;	//�J�ڐ�V�[���̃|�C���^��Ԃ�
		}
	}
	return this;	//�J�ڂȂ�
}

/*! =====================================================================================
@brief	���[�f�B���O�i�ʃX���b�h�Ŏ��s����܂��j
@param	void
@return void
====================================================================================== */
void LoadScene::Loading() {
	m_pNextScene->Initialize();	//�V�[���̏������J�n
	*m_pLoadingFlg = false;		//�������I��
}

/*! =====================================================================================
@brief	�V�[���J�ڂ̏�������
@param	void
@return bool	�V�[���J�ڂ���Ftrue
====================================================================================== */
bool LoadScene::CheckSceneTransition() {

	//�V�[���J�n�E�I�����̃t�F�[�h���̓V�[���J�ڂ��󂯕t���Ȃ�
	//�܂��A��x�V�[���J�ڂ����܂������Ƃ̑J�ڐ�ύX���󂯕t���Ȃ�
	if (m_pFadeSprite->GetFadingState() == true || m_nextSceneID != 0) {
		return false;
	}

	//���[�f�B���O��������
	if (*m_pLoadingFlg == true) {
		return false;	//���[�f�B���O��
	}
	else {
		m_nextSceneID = 1;
		return false;	//���[�f�B���O����
	}
}