/*! =====================================================================================
@file		DebugNew.h
@brief		�f�o�b�O���[�h���A���������[�N���o�E�t�@�C���ƍs����肵�ă��O���o�͂���
@author		Takuya Kawakami
@date		2016.11.02	�V�K�쐬
====================================================================================== */
#pragma once
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC	//malloc�Ŋm�ۂ��ꂽ�q�[�v�̈���Ď��B�i���������[�N�̌����ł���t�@�C���ƍs����肵�ďo�́j
#include <stdlib.h> 
#include <crtdbg.h>

#define DEBUG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) //new�Ŋm�ۂ��ꂽ�q�[�v�̈���Ď��B�i���������[�N�̌����ł���t�@�C���ƍs����肵�ďo�́j
#define new DEBUG_NEW

#endif // _DEBUG
