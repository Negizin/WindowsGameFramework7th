/*! =====================================================================================
@file		TimerSystem.h
@brief		タイマー
@author		TakuyaKawakami
@date		2016.03.15	新規作成
====================================================================================== */
#pragma once
#define		WIN32_LEAN_AND_MEAN
#include	<Windows.h>
#include	<Mmsystem.h>
#pragma	comment(lib, "winmm.lib")

class TimerSystem {
public:
	TimerSystem();
	~TimerSystem();

	/*! =====================================================================================
	@brief	初期化処理
	@param	void
	@return HRESULT：成功＝S_OK
	====================================================================================== */
	HRESULT	Initialize();

	/*! =====================================================================================
	@brief	FPS制御：更新可能ならばtrueを返す
	@param	void
	@return bool
	====================================================================================== */
	bool	ControlFPS();

private:
	//Data
	bool m_fixedFrameRateFlg;	//true:固定長フレームレート、false:可変長フレームレート
	LARGE_INTEGER	m_timeStart;
	LARGE_INTEGER	m_timeEnd;
	LARGE_INTEGER	m_timerFreq;
	DWORD			m_sleepTime;
};
