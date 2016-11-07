#include "Timer.h"
#include	"../../../BaseSystem/Private/Timer/TimerSystemNS.h"

namespace {
	static	float	g_timeScale = 1.0f;		//���Ԍo�ߑ��x
}

/*! =====================================================================================
@brief	���O�̃t���[�����猻�݂̃t���[���Ԃɗv�������Ԃ��擾
@param	void
@return float
====================================================================================== */
float Timer::GetDeltaTime() {
	return g_timeScale * g_deltaTime;
}

/*! =====================================================================================
@brief	���Ԍo�ߑ��x���擾�i�f�t�H���g�ł�1.0f�j
@param	void
@return float
====================================================================================== */
float Timer::GetTimeScale() {
	return g_timeScale;
}

/*! =====================================================================================
@brief	���Ԍo�ߑ��x��ݒ�i�f�t�H���g�ł�1.0f�j
@param	float
@return void
====================================================================================== */
void Timer::SetTimeScale(float _parameter) {
	g_timeScale = _parameter;
}
