/*! =====================================================================================
@file		Input.h
@brief		���͋@�\�Ǘ��N���X
@author		Takuya Kawakami
@date		2016.11.03	�V�K�쐬
====================================================================================== */
#pragma once
#include	"KeyboardData.h"
#include	"XInputControllerData.h"

//���͂̏�ԊǗ�
class InputSystem {
public:
	InputSystem();
	~InputSystem();

	/*! =====================================================================================
	@brief	����������
	@param	void
	@return void
	====================================================================================== */
	void	Initialize();

	/*! =====================================================================================
	@brief	�S���̓f�o�C�X�̏�ԍX�V
	@param	void
	@return void
	====================================================================================== */
	void	UpdateAllInputDevice();

private:
	void	UpdateKeyboard();
	void	UpdateController();
};