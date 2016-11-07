#include	"TimerSystem.h"
#include	"TimerSystemNS.h"


//�������	�I�I�I�����I�ɊO���t�@�C������̓ǂݍ��݂ֈڍs��\��I�I�I
namespace {
	const	float	FRAME_RATE = 120.0f;					// �ő�ڕWfps(frames/sec)
	const	float	MIN_FRAME_RATE = 60.0f;					// �Œዖ�efps
	const	float	BEST_TIME = 1.0f / FRAME_RATE;			// fps�ڕW�B���B�����̂P�t���[���Ԍo�ߎ���
	const	float	BORDER_TIME = 1.0f / MIN_FRAME_RATE;	// fps�Œ᎞�̂P�t���[���Ԍo�ߎ���
}

/*! =====================================================================================
@brief	�R���X�g���N�^
@param	void
====================================================================================== */
TimerSystem::TimerSystem() {
	m_fixedFrameRateFlg = false;
}

/*! =====================================================================================
@brief	�f�X�g���N�^
@param	void
====================================================================================== */
TimerSystem::~TimerSystem() {

}

/*! =====================================================================================
@brief	����������
@param	void
@return HRESULT
====================================================================================== */
HRESULT	TimerSystem::Initialize() {
	if (QueryPerformanceFrequency(&m_timerFreq) == false) {
		return E_FAIL;
	}
	QueryPerformanceCounter(&m_timeStart);
	return S_OK;
}

/*! =====================================================================================
@brief	FPS����F�X�V�\�Ȃ��true��Ԃ�
@param	void
@return bool
====================================================================================== */
bool	TimerSystem::ControlFPS() {

	//�ŏI�t���[������̌o�ߎ��Ԏ擾
	QueryPerformanceCounter(&m_timeEnd);
	g_deltaTime = (float) (m_timeEnd.QuadPart - m_timeStart.QuadPart) / (float) m_timerFreq.QuadPart;

	if (m_fixedFrameRateFlg == true) {	//�Œ蒷�t���[�����[�g��ڎw��

		//�ڕW�t���[�����[�g�܂ŗP�\������ꍇ�A�X���[�v
		if (g_deltaTime < BEST_TIME) {
			m_sleepTime = (DWORD) ((BEST_TIME - g_deltaTime) * 1000);
			timeBeginPeriod(1);
			Sleep(m_sleepTime);
			timeEndPeriod(1);
			return false;
		}

		//�Œዖ�e�t���[�����[�g��B���ł��Ă��Ȃ��ꍇ
		if (g_deltaTime > BORDER_TIME) {
			//
			//	�p�[�e�B�N���V�X�e�������d������R�[���Ƃ�
			//
		}
	}
	else {	
		//�ϒ��t���[�����[�g�B�ڕW���[�g�܂ŗ]�T�������Ă��X���[�v���Ȃ����A
		//�ő�l�𖳐����ɂ����Ƃ���APC����ى�����������悤�ɂȂ����B
		//�b��I�ɌŒ蒷�̔{�ɍő�l��ݒ肷�邱�ƂŁA���������B
		if (g_deltaTime < (BEST_TIME / 2.0f)) {
			m_sleepTime = (DWORD) (((BEST_TIME / 2.0f) - g_deltaTime) * 1000);
			timeBeginPeriod(1);
			Sleep(m_sleepTime);
			timeEndPeriod(1);
			return false;
		}
	}

	//�O�l�X�V
	m_timeStart = m_timeEnd;

	return true;
}