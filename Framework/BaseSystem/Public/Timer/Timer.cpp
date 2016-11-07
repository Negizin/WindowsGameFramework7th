#include "Timer.h"
#include	"../../../BaseSystem/Private/Timer/TimerSystemNS.h"

namespace {
	static	float	g_timeScale = 1.0f;		//時間経過速度
}

/*! =====================================================================================
@brief	直前のフレームから現在のフレーム間に要した時間を取得
@param	void
@return float
====================================================================================== */
float Timer::GetDeltaTime() {
	return g_timeScale * g_deltaTime;
}

/*! =====================================================================================
@brief	時間経過速度を取得（デフォルトでは1.0f）
@param	void
@return float
====================================================================================== */
float Timer::GetTimeScale() {
	return g_timeScale;
}

/*! =====================================================================================
@brief	時間経過速度を設定（デフォルトでは1.0f）
@param	float
@return void
====================================================================================== */
void Timer::SetTimeScale(float _parameter) {
	g_timeScale = _parameter;
}
