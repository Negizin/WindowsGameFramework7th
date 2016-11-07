/*! =====================================================================================
@file		TimerSystem.h
@brief		�^�C�}�[
@author		TakuyaKawakami
@date		2016.03.15	�V�K�쐬
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
	@brief	����������
	@param	void
	@return HRESULT�F������S_OK
	====================================================================================== */
	HRESULT	Initialize();

	/*! =====================================================================================
	@brief	FPS����F�X�V�\�Ȃ��true��Ԃ�
	@param	void
	@return bool
	====================================================================================== */
	bool	ControlFPS();

private:
	//Data
	bool m_fixedFrameRateFlg;	//true:�Œ蒷�t���[�����[�g�Afalse:�ϒ��t���[�����[�g
	LARGE_INTEGER	m_timeStart;
	LARGE_INTEGER	m_timeEnd;
	LARGE_INTEGER	m_timerFreq;
	DWORD			m_sleepTime;
};
