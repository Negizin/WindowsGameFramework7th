/*! =====================================================================================
@file		XInputControllerData.h
@brief		Xinput�f�[�^
@author		Takuya Kawakami
@date		2015.12.15
====================================================================================== */

#pragma once
#define		WIN32_LEAN_AND_MEAN
#include	<windows.h>
#include	<XInput.h>
#pragma	comment (lib, "Xinput.lib")

//���͏�Ԏ擾�p�}�X�N
namespace XCODE {
	enum {
		D_UP = XINPUT_GAMEPAD_DPAD_UP,
		D_DONW = XINPUT_GAMEPAD_DPAD_DOWN,
		D_LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
		D_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
		START = XINPUT_GAMEPAD_START,
		BACK = XINPUT_GAMEPAD_BACK,
		THUMB_L = XINPUT_GAMEPAD_LEFT_THUMB,
		THUMB_R = XINPUT_GAMEPAD_RIGHT_THUMB,
		LB = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RB = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		A = XINPUT_GAMEPAD_A,
		B = XINPUT_GAMEPAD_B,
		X = XINPUT_GAMEPAD_X,
		Y = XINPUT_GAMEPAD_Y,
	};
}

//���͏�ԊǗ��p
struct CONTROLER_STATE {
	XINPUT_STATE old;		//�O�t���[���ł̓��͏��
	XINPUT_STATE hold;		//���݂̓��͏��
	XINPUT_STATE trigger;	//�g���K�[����p�i�������t���[���j
	XINPUT_STATE release;	//�����[�X����p�i�������t���[���j
	bool bConnected;		//�ڑ����
};