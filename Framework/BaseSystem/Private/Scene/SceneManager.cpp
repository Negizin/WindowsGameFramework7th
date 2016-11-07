#include	"SceneManager.h"
#include	"../../../BaseSystem/Public/Common/Common.h"
#include	"LoadingScene.h"
//#include	"TitleScene.h"
//#include	"..//Game/GameScene.h"
#include	<thread>

/*! =====================================================================================
@brief	�R���X�g���N�^
@param	void
====================================================================================== */
SceneManager::SceneManager() {
	m_bNowLoading = true;
}

/*! =====================================================================================
@brief	�f�X�g���N�^
@param	void
====================================================================================== */
SceneManager::~SceneManager() {
	SafeDelete(m_pNowScene);
	SafeDelete(m_pLoadingScene);
}

/*! =====================================================================================
@brief	����������
@param	void
@return void
====================================================================================== */
void	SceneManager::Initialize() {
	//m_pNowScene = new GameScene();
}

/*! =====================================================================================
@brief	�X�V����
@param	void
@return void
====================================================================================== */
void	SceneManager::Update() {

	if (m_pNowScene == nullptr) {
		return;
	}

	//�V�[���̍X�V����
	m_pNextScene = m_pNowScene->Update();

	//�V�[���J�ڏ����𖞂����ꂽ�Ƃ��A�J�ڐ�V�[���̃|�C���^���Ԃ�i�J�ڂȂ��̏ꍇ�̓V�[����this�|�C���^���Ԃ�j
	if (m_pNextScene != m_pNowScene) {

		//���[�f�B���O�̊����ɂ��V�[���J�ڂ̏ꍇ
		if (m_bNowLoading == true) {
			m_bNowLoading = false;		//���[�f�B���OOFF
			m_pNowScene = m_pNextScene;	//�J�ڐ�V�[�����Z�b�g
		}
		//�ʏ�̃Q�[���V�[������ʂ̃V�[���֑J�ڂ���ꍇ
		else {
			m_bNowLoading = true;				//���[�f�B���OON
			//m_pLoadingScene->Initialize(m_pNextScene);	//�J�ڐ�V�[���̃|�C���^�����[�f�B���O�V�[���ɓn��
			m_pNextScene = m_pNowScene = m_pLoadingScene;	//���[�f�B���O�p�V�[�����Z�b�g
		}
	}

}

/*! =====================================================================================
@brief	�`�揈��
@param	void
@return void
====================================================================================== */
void	SceneManager::RenderScene() {

	if (m_pNowScene == nullptr) {
		return;
	}

	m_pNowScene->UpdateRenderer();
}

/*! =====================================================================================
@brief	�J�ڐ�V�[���̗����グ
@param	void
@return void
====================================================================================== */
void SceneManager::NextSceneLaunch() {

}
