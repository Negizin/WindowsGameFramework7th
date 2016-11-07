#include	"Input.h"
#include	"../../../BaseSystem/Private/Input/InputSystemNS.h"
#include	<stdlib.h>

/*! =====================================================================================
@brief	�L�[�{�[�h�F�L�[�������������Ă����Ԃ𔻒�
@param	��Ԃ��m�F�������L�[�̃}�X�N�iKCODE�̖��O��Ԃ��Q�Ƃ��Ă��������j
@return bool
====================================================================================== */
bool Input::GetKeyHold(unsigned	long long KCODE_MASK) {
	return	bool((g_keyboard.hold & KCODE_MASK) == KCODE_MASK);
}

/*! =====================================================================================
@brief	�L�[�{�[�h�F�L�[�������ꂽ�u�Ԃ̏�Ԃ𔻒�
@param	��Ԃ��m�F�������L�[�̃}�X�N�iKCODE�̖��O��Ԃ��Q�Ƃ��Ă��������j
@return bool
====================================================================================== */
bool Input::GetKeyTrigger(unsigned	long long KCODE_MASK) {
	return	bool((g_keyboard.trigger & KCODE_MASK) != 0);
}

/*! =====================================================================================
@brief	�L�[�{�[�h�F�L�[�������ꂽ�u�Ԃ̏�Ԃ𔻒�
@param	��Ԃ��m�F�������L�[�̃}�X�N�iKCODE�̖��O��Ԃ��Q�Ƃ��Ă��������j
@return bool
====================================================================================== */
bool Input::GetKeyRelease(unsigned	long long KCODE_MASK) {
	return	bool((g_keyboard.release & KCODE_MASK) != 0);
}

/*! =====================================================================================
@brief	�R���g���[���F�{�^���������������Ă����Ԃ𔻒�
@param	�O�`�R�̃R���g���[���ԍ�
@param	��Ԃ��m�F�������{�^���̃}�X�N�iXCODE�̖��O��Ԃ��Q�Ƃ��Ă��������j
@return bool
====================================================================================== */
bool Input::GetPadHold(int controller_n, int XCODE_MASK) {
	return	bool((g_controllers[controller_n].hold.Gamepad.wButtons & XCODE_MASK) == XCODE_MASK);
}

/*! =====================================================================================
@brief	�R���g���[���F�{�^���������ꂽ�u�Ԃ̏�Ԃ𔻒�
@param	�O�`�R�̃R���g���[���ԍ�
@param	��Ԃ��m�F�������{�^���̃}�X�N�iXCODE�̖��O��Ԃ��Q�Ƃ��Ă��������j
@return bool
====================================================================================== */
bool Input::GetPadTrigger(int controller_n, int XCODE_MASK) {
	return	bool((g_controllers[controller_n].trigger.Gamepad.wButtons & XCODE_MASK) != 0);
}

/*! =====================================================================================
@brief	�R���g���[���F�{�^���������ꂽ�u�Ԃ̏�Ԃ𔻒�
@param	�O�`�R�̃R���g���[���ԍ�
@param	��Ԃ��m�F�������{�^���̃}�X�N�iXCODE�̖��O��Ԃ��Q�Ƃ��Ă��������j
@return bool
====================================================================================== */
bool Input::GetPadRelease(int controller_n, int XCODE_MASK) {
	return	bool((g_controllers[controller_n].release.Gamepad.wButtons & XCODE_MASK) != 0);
}

/*! =====================================================================================
@brief	XBOX�R���g���[���F���X�e�B�b�N��X���̒l���擾
@param	0�`3�̃R���g���[���ԍ�
@return -1.0 ~ 1.0
====================================================================================== */
float Input::GetPadAxisLX(int controller_n) {
	if (abs(g_controllers[controller_n].hold.Gamepad.sThumbLX) < DEADZONE_THUMB) {
		return 0.0f;
	}
	return	g_controllers[controller_n].hold.Gamepad.sThumbLX / 32768.0f;
}

/*! =====================================================================================
@brief	XBOX�R���g���[���F���X�e�B�b�N��Y���̒l���擾
@param	0�`3�̃R���g���[���ԍ�
@return -1.0 ~ 1.0
====================================================================================== */
float Input::GetPadAxisLY(int controller_n) {
	if (abs(g_controllers[controller_n].hold.Gamepad.sThumbLY) < DEADZONE_THUMB) {
		return 0.0f;
	}
	return	g_controllers[controller_n].hold.Gamepad.sThumbLY / 32768.0f;
}

/*! =====================================================================================
@brief	XBOX�R���g���[���F�E�X�e�B�b�N��X���̒l���擾
@param	0�`3�̃R���g���[���ԍ�
@return -1.0 ~ 1.0
====================================================================================== */
float Input::GetPadAxisRX(int controller_n) {
	if (abs(g_controllers[controller_n].hold.Gamepad.sThumbRX) < DEADZONE_THUMB) {
		return 0.0f;
	}
	return	g_controllers[controller_n].hold.Gamepad.sThumbRX / 32768.0f;
}

/*! =====================================================================================
@brief	XBOX�R���g���[���F�E�X�e�B�b�N��Y���̒l���擾
@param	0�`3�̃R���g���[���ԍ�
@return -1.0 ~ 1.0
====================================================================================== */
float Input::GetPadAxisRY(int controller_n) {
	if (abs(g_controllers[controller_n].hold.Gamepad.sThumbRY) < DEADZONE_THUMB) {
		return 0.0f;
	}
	return	g_controllers[controller_n].hold.Gamepad.sThumbRY / 32768.0f;
}

/*! =====================================================================================
@brief	XBOX�R���g���[���F���g���K�[�̒l���擾
@param	0�`3�̃R���g���[���ԍ�
@return -1.0 ~ 1.0
====================================================================================== */
float Input::GetPadLT(int controller_n) {
	if (abs(g_controllers[controller_n].hold.Gamepad.bLeftTrigger) < DEADZONE_TRIGGER) {
		return 0.0f;
	}
	return g_controllers[controller_n].hold.Gamepad.bLeftTrigger / 255.0f;
}

/*! =====================================================================================
@brief	XBOX�R���g���[���F�E�g���K�[�̒l���擾
@param	0�`3�̃R���g���[���ԍ�
@return -1.0 ~ 1.0
====================================================================================== */
float Input::GetPadRT(int controller_n) {
	if (abs(g_controllers[controller_n].hold.Gamepad.bRightTrigger) < DEADZONE_TRIGGER) {
		return 0.0f;
	}
	return g_controllers[controller_n].hold.Gamepad.bRightTrigger / 255.0f;
}
