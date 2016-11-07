/*! =====================================================================================
@file		InputSystemNS.h
@brief		���͂Ɋւ���t���[�����[�N���ƃQ�[���������ł̃C���^�[�t�F�[�X�ɋ��ʂ̃f�[�^��ێ����閼�O���
@author		Takuya Kawakami
@date		2016.11.03	�V�K�쐬
====================================================================================== */
#pragma once
#include	"KeyboardData.h"
#include	"XInputControllerData.h"

namespace {
	const	static	int		MAX_CONTROLLERS = 4;			//�R���g���[���̍ő吔
	static	CONTROLER_STATE	g_controllers[MAX_CONTROLLERS];	//�R���g���[���̓��̓f�[�^
	static	KEYBOARD_STATE	g_keyboard;						//�L�[�{�[�h�̓��̓f�[�^

	const	static	short	DEADZONE_THUMB = (short) (32767.0f * 0.2f);	//�X�e�B�b�N�̃f�b�h�]�[��
	const	static	unsigned char	DEADZONE_TRIGGER = (unsigned char) (255.0f * 0.2f);	//�g���K�[�f�b�h�]�[��
}
