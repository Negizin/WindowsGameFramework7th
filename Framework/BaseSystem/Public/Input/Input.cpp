#include	"Input.h"
#include	"../../../BaseSystem/Private/Input/InputSystemNS.h"
#include	<stdlib.h>

/*! =====================================================================================
@brief	キーボード：キーが押し続けられている状態を判定
@param	状態を確認したいキーのマスク（KCODEの名前空間を参照してください）
@return bool
====================================================================================== */
bool Input::GetKeyHold(unsigned	long long KCODE_MASK) {
	return	bool((g_keyboard.hold & KCODE_MASK) == KCODE_MASK);
}

/*! =====================================================================================
@brief	キーボード：キーが押された瞬間の状態を判定
@param	状態を確認したいキーのマスク（KCODEの名前空間を参照してください）
@return bool
====================================================================================== */
bool Input::GetKeyTrigger(unsigned	long long KCODE_MASK) {
	return	bool((g_keyboard.trigger & KCODE_MASK) != 0);
}

/*! =====================================================================================
@brief	キーボード：キーが離された瞬間の状態を判定
@param	状態を確認したいキーのマスク（KCODEの名前空間を参照してください）
@return bool
====================================================================================== */
bool Input::GetKeyRelease(unsigned	long long KCODE_MASK) {
	return	bool((g_keyboard.release & KCODE_MASK) != 0);
}

/*! =====================================================================================
@brief	コントローラ：ボタンが押し続けられている状態を判定
@param	０～３のコントローラ番号
@param	状態を確認したいボタンのマスク（XCODEの名前空間を参照してください）
@return bool
====================================================================================== */
bool Input::GetPadHold(int controller_n, int XCODE_MASK) {
	return	bool((g_controllers[controller_n].hold.Gamepad.wButtons & XCODE_MASK) == XCODE_MASK);
}

/*! =====================================================================================
@brief	コントローラ：ボタンが押された瞬間の状態を判定
@param	０～３のコントローラ番号
@param	状態を確認したいボタンのマスク（XCODEの名前空間を参照してください）
@return bool
====================================================================================== */
bool Input::GetPadTrigger(int controller_n, int XCODE_MASK) {
	return	bool((g_controllers[controller_n].trigger.Gamepad.wButtons & XCODE_MASK) != 0);
}

/*! =====================================================================================
@brief	コントローラ：ボタンが離された瞬間の状態を判定
@param	０～３のコントローラ番号
@param	状態を確認したいボタンのマスク（XCODEの名前空間を参照してください）
@return bool
====================================================================================== */
bool Input::GetPadRelease(int controller_n, int XCODE_MASK) {
	return	bool((g_controllers[controller_n].release.Gamepad.wButtons & XCODE_MASK) != 0);
}

/*! =====================================================================================
@brief	XBOXコントローラ：左スティックのX軸の値を取得
@param	0～3のコントローラ番号
@return -1.0 ~ 1.0
====================================================================================== */
float Input::GetPadAxisLX(int controller_n) {
	if (abs(g_controllers[controller_n].hold.Gamepad.sThumbLX) < DEADZONE_THUMB) {
		return 0.0f;
	}
	return	g_controllers[controller_n].hold.Gamepad.sThumbLX / 32768.0f;
}

/*! =====================================================================================
@brief	XBOXコントローラ：左スティックのY軸の値を取得
@param	0～3のコントローラ番号
@return -1.0 ~ 1.0
====================================================================================== */
float Input::GetPadAxisLY(int controller_n) {
	if (abs(g_controllers[controller_n].hold.Gamepad.sThumbLY) < DEADZONE_THUMB) {
		return 0.0f;
	}
	return	g_controllers[controller_n].hold.Gamepad.sThumbLY / 32768.0f;
}

/*! =====================================================================================
@brief	XBOXコントローラ：右スティックのX軸の値を取得
@param	0～3のコントローラ番号
@return -1.0 ~ 1.0
====================================================================================== */
float Input::GetPadAxisRX(int controller_n) {
	if (abs(g_controllers[controller_n].hold.Gamepad.sThumbRX) < DEADZONE_THUMB) {
		return 0.0f;
	}
	return	g_controllers[controller_n].hold.Gamepad.sThumbRX / 32768.0f;
}

/*! =====================================================================================
@brief	XBOXコントローラ：右スティックのY軸の値を取得
@param	0～3のコントローラ番号
@return -1.0 ~ 1.0
====================================================================================== */
float Input::GetPadAxisRY(int controller_n) {
	if (abs(g_controllers[controller_n].hold.Gamepad.sThumbRY) < DEADZONE_THUMB) {
		return 0.0f;
	}
	return	g_controllers[controller_n].hold.Gamepad.sThumbRY / 32768.0f;
}

/*! =====================================================================================
@brief	XBOXコントローラ：左トリガーの値を取得
@param	0～3のコントローラ番号
@return -1.0 ~ 1.0
====================================================================================== */
float Input::GetPadLT(int controller_n) {
	if (abs(g_controllers[controller_n].hold.Gamepad.bLeftTrigger) < DEADZONE_TRIGGER) {
		return 0.0f;
	}
	return g_controllers[controller_n].hold.Gamepad.bLeftTrigger / 255.0f;
}

/*! =====================================================================================
@brief	XBOXコントローラ：右トリガーの値を取得
@param	0～3のコントローラ番号
@return -1.0 ~ 1.0
====================================================================================== */
float Input::GetPadRT(int controller_n) {
	if (abs(g_controllers[controller_n].hold.Gamepad.bRightTrigger) < DEADZONE_TRIGGER) {
		return 0.0f;
	}
	return g_controllers[controller_n].hold.Gamepad.bRightTrigger / 255.0f;
}
