#include	"FadeSprite.h"

namespace {
	const	float	FADE_TIME = 1.0f;
}

/*! =====================================================================================
@brief	�R���X�g���N�^
@param	void
====================================================================================== */
FadeSprite::FadeSprite() {
	m_bFirstFrame = true;
	m_bFadeIN = true;
	m_bFadeOUT = false;
	m_timer = 0;
}

/*! =====================================================================================
@brief	�f�X�g���N�^
@param	void
====================================================================================== */
FadeSprite::~FadeSprite() {
}

/*! =====================================================================================
@brief	�X�V����
@param	void
@return void
====================================================================================== */
void FadeSprite::Update() {

	//�V�[���J�n�ŏ��̃t���[���́A�V�[���̏������ɂ��Timer��GetDeltaTime�̒l���傫������
	//�t�F�[�h���������@�\���Ȃ�����u�ŏI��邱�Ƃ�����̂Ńp�X����K�v������
	if (m_bFirstFrame == true) {
		m_bFirstFrame = false;
		return;
	}

	//�^�C�}�[����
	m_timer += Timer::GetDeltaTime();
	float	_parameter = (m_timer / FADE_TIME) * Math::PI * 0.5f;

	//�t�F�[�h�C������
	if (m_bFadeIN) {
		sinf(_parameter);		//�T�C���J�[�u�ŕ�ԁi��������s�����j
		if (m_timer > FADE_TIME) {
			m_bFadeIN = false;	//�t�F�[�h�C���I��
			Activate(false);	//�X�V�E�`��OFF
		}
	}

	//�t�F�[�h�A�E�g����
	if (m_bFadeOUT) {
		cosf(_parameter);		//�R�T�C���J�[�u�ŕ�ԁi�s�������瓧���j
		if (m_timer > FADE_TIME) {
			m_bFadeOUT = false;	//�t�F�[�h�A�E�g�I��
			Activate(false);	//�X�V�E�`��OFF
		}
	}
}

/*! =====================================================================================
@brief	�t�F�[�h�A�E�g�J�n
@param	void
@return void
====================================================================================== */
void FadeSprite::StartFadeOut() {
	if (m_bFadeIN | m_bFadeOUT) {
		return;			//���Ƀt�F�[�h���̏ꍇ�͎󂯕t���Ȃ�
	}
	m_timer = 0;		//�^�C�}�[������
	m_bFadeOUT = true;	//�t�F�[�h�A�E�gON
	Activate(true);		//�X�V�E�`��ON
}

/*! =====================================================================================
@brief	�t�F�[�h��Ԏ擾
@param	void
@return bool:�t�F�[�h���Ȃ��true��Ԃ�
====================================================================================== */
bool FadeSprite::GetFadingState() const {
	return (m_bFadeIN | m_bFadeOUT);
}