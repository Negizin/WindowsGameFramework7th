/*! =====================================================================================
@file		Common.h
@brief		�x�[�X�ƂȂ�e�틤�ʃv���v���Z�X�A�C���N���[�h�A���C�u�����A�}�N��
@author		Takuya Kawakami
@date		2016.03.14	�V�K�쐬
====================================================================================== */
#pragma once

//	Windows.h �C���N���[�h�t�@�C��
#define WIN32_LEAN_AND_MEAN
#include	<Windows.h>

//	TCHAR�Ή�(�J�����̐ݒ�ɉ�������������g�p����)
#include	"../../../BaseSystem/Private/Common/TCHARString.h"

//	�f�o�b�O���[�h���A���������[�N���o����
#include	"../../../BaseSystem/Private/Common/DebugNew.h"

//	SafeDelete�n�A�t�[���v���[�t�@�\�t������}�N��
#include	"../../../BaseSystem/Private/Common/SafeFunction.h"