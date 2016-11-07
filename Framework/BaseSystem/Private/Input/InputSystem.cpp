#include	"InputSystem.h"
#include	"InputSystemNS.h"

/*! =====================================================================================
@brief	�R���X�g���N�^
@param	void
====================================================================================== */
InputSystem::InputSystem() {
	Initialize();
}

/*! =====================================================================================
@brief	�f�X�g���N�^
@param	void
====================================================================================== */
InputSystem::~InputSystem() {
}

/*! =====================================================================================
@brief	����������
@param	void
@return void
====================================================================================== */
void InputSystem::Initialize() {
	SecureZeroMemory(&g_keyboard, sizeof(KEYBOARD_STATE));
	SecureZeroMemory(g_controllers, sizeof(CONTROLER_STATE)*MAX_CONTROLLERS);
}

/*! =====================================================================================
@brief	�S���̓f�o�C�X�̏�ԍX�V
@param	void
@return void
====================================================================================== */
void InputSystem::UpdateAllInputDevice() {
	UpdateKeyboard();
	UpdateController();
}

/*! =====================================================================================
@brief	�L�[�{�[�h�X�V
@param	void
@return void
====================================================================================== */
void InputSystem::UpdateKeyboard() {
	g_keyboard.hold = 0x000000000000000000;		//�o�b�t�@�N���A

	if (::GetAsyncKeyState(VK_ESCAPE))		g_keyboard.hold |= KCODE::ESC;		//Escape�L�[
	if (::GetAsyncKeyState(VK_TAB))			g_keyboard.hold |= KCODE::TAB;		//Tabe�L�[
	if (::GetAsyncKeyState(VK_LSHIFT))		g_keyboard.hold |= KCODE::SHIFT_L;	//LSHIFT�L�[
	if (::GetAsyncKeyState(VK_LCONTROL))	g_keyboard.hold |= KCODE::CTRL_L;	//LSHIFT�L�[
	if (::GetAsyncKeyState(VK_LMENU))		g_keyboard.hold |= KCODE::ALT_L;	//��alt�L�[
	if (::GetAsyncKeyState(VK_SPACE))		g_keyboard.hold |= KCODE::SPACE;	//�X�y�[�X
	if (::GetAsyncKeyState(VK_BACK))		g_keyboard.hold |= KCODE::BS;		//BackSpace�L�[
	if (::GetAsyncKeyState(VK_RETURN))		g_keyboard.hold |= KCODE::ENTER;	//Enter�L�[
	if (::GetAsyncKeyState(VK_RSHIFT))		g_keyboard.hold |= KCODE::SHIFT_R;	//RSHIFT�L�[
	if (::GetAsyncKeyState(VK_LEFT))		g_keyboard.hold |= KCODE::LEFT;		//��
	if (::GetAsyncKeyState(VK_UP))			g_keyboard.hold |= KCODE::UP;		//��
	if (::GetAsyncKeyState(VK_RIGHT))		g_keyboard.hold |= KCODE::RIGHT;	//��
	if (::GetAsyncKeyState(VK_DOWN))		g_keyboard.hold |= KCODE::DOWN;		//��

	if (::GetAsyncKeyState(VK_NUMPAD0))		g_keyboard.hold |= KCODE::NUMP_0;	//�e���L�[0
	if (::GetAsyncKeyState(VK_NUMPAD1))		g_keyboard.hold |= KCODE::NUMP_1;	//�e���L�[1
	if (::GetAsyncKeyState(VK_NUMPAD2))		g_keyboard.hold |= KCODE::NUMP_2;	//�e���L�[2
	if (::GetAsyncKeyState(VK_NUMPAD3))		g_keyboard.hold |= KCODE::NUMP_3;	//�e���L�[3
	if (::GetAsyncKeyState(VK_NUMPAD4))		g_keyboard.hold |= KCODE::NUMP_4;	//�e���L�[4
	if (::GetAsyncKeyState(VK_NUMPAD5))		g_keyboard.hold |= KCODE::NUMP_5;	//�e���L�[5
	if (::GetAsyncKeyState(VK_NUMPAD6))		g_keyboard.hold |= KCODE::NUMP_6;	//�e���L�[6
	if (::GetAsyncKeyState(VK_NUMPAD7))		g_keyboard.hold |= KCODE::NUMP_7;	//�e���L�[7
	if (::GetAsyncKeyState(VK_NUMPAD8))		g_keyboard.hold |= KCODE::NUMP_8;	//�e���L�[8
	if (::GetAsyncKeyState(VK_NUMPAD9))		g_keyboard.hold |= KCODE::NUMP_9;	//�e���L�[9

	if (::GetAsyncKeyState(VK_0))		g_keyboard.hold |= KCODE::NUM_0;	//0
	if (::GetAsyncKeyState(VK_1))		g_keyboard.hold |= KCODE::NUM_1;	//1
	if (::GetAsyncKeyState(VK_2))		g_keyboard.hold |= KCODE::NUM_2;	//2
	if (::GetAsyncKeyState(VK_3))		g_keyboard.hold |= KCODE::NUM_3;	//3
	if (::GetAsyncKeyState(VK_4))		g_keyboard.hold |= KCODE::NUM_4;	//4
	if (::GetAsyncKeyState(VK_5))		g_keyboard.hold |= KCODE::NUM_5;	//5
	if (::GetAsyncKeyState(VK_6))		g_keyboard.hold |= KCODE::NUM_6;	//6
	if (::GetAsyncKeyState(VK_7))		g_keyboard.hold |= KCODE::NUM_7;	//7
	if (::GetAsyncKeyState(VK_8))		g_keyboard.hold |= KCODE::NUM_8;	//8

	if (::GetAsyncKeyState(VK_A))		g_keyboard.hold |= KCODE::A;		//A
	if (::GetAsyncKeyState(VK_B))		g_keyboard.hold |= KCODE::B;		//B
	if (::GetAsyncKeyState(VK_C))		g_keyboard.hold |= KCODE::C;		//C
	if (::GetAsyncKeyState(VK_D))		g_keyboard.hold |= KCODE::D;		//D
	if (::GetAsyncKeyState(VK_E))		g_keyboard.hold |= KCODE::E;		//E
	if (::GetAsyncKeyState(VK_F))		g_keyboard.hold |= KCODE::F;		//F
	if (::GetAsyncKeyState(VK_G))		g_keyboard.hold |= KCODE::G;		//G
	if (::GetAsyncKeyState(VK_H))		g_keyboard.hold |= KCODE::H;		//H
	if (::GetAsyncKeyState(VK_I))		g_keyboard.hold |= KCODE::I;		//I
	if (::GetAsyncKeyState(VK_J))		g_keyboard.hold |= KCODE::J;		//J
	if (::GetAsyncKeyState(VK_K))		g_keyboard.hold |= KCODE::K;		//K
	if (::GetAsyncKeyState(VK_L))		g_keyboard.hold |= KCODE::L;		//L
	if (::GetAsyncKeyState(VK_M))		g_keyboard.hold |= KCODE::M;		//M
	if (::GetAsyncKeyState(VK_N))		g_keyboard.hold |= KCODE::N;		//N
	if (::GetAsyncKeyState(VK_O))		g_keyboard.hold |= KCODE::O;		//O
	if (::GetAsyncKeyState(VK_P))		g_keyboard.hold |= KCODE::P;		//P
	if (::GetAsyncKeyState(VK_Q))		g_keyboard.hold |= KCODE::Q;		//Q
	if (::GetAsyncKeyState(VK_R))		g_keyboard.hold |= KCODE::R;		//R
	if (::GetAsyncKeyState(VK_S))		g_keyboard.hold |= KCODE::S;		//S
	if (::GetAsyncKeyState(VK_T))		g_keyboard.hold |= KCODE::T;		//T
	if (::GetAsyncKeyState(VK_U))		g_keyboard.hold |= KCODE::U;		//U
	if (::GetAsyncKeyState(VK_V))		g_keyboard.hold |= KCODE::V;		//V
	if (::GetAsyncKeyState(VK_W))		g_keyboard.hold |= KCODE::W;		//W
	if (::GetAsyncKeyState(VK_X))		g_keyboard.hold |= KCODE::X;		//X
	if (::GetAsyncKeyState(VK_Y))		g_keyboard.hold |= KCODE::Y;		//Y
	if (::GetAsyncKeyState(VK_Z))		g_keyboard.hold |= KCODE::Z;		//Z

	g_keyboard.trigger = (g_keyboard.old ^ g_keyboard.hold) & g_keyboard.hold;
	g_keyboard.release = (g_keyboard.old ^ g_keyboard.hold) & g_keyboard.old;
	g_keyboard.old = g_keyboard.hold;
}

/*! =====================================================================================
@brief	�R���g���[���X�V
@param	void
@return void
====================================================================================== */
void InputSystem::UpdateController() {
	DWORD _dwResult;
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++) {
		_dwResult = XInputGetState(i, &g_controllers[i].hold);

		if (_dwResult == ERROR_DEVICE_NOT_CONNECTED) {
			g_controllers[i].bConnected = false;
			SecureZeroMemory(&g_controllers[i], sizeof(CONTROLER_STATE));
			continue;
		}
		else {
			g_controllers[i].bConnected = true;
			g_controllers[i].trigger.Gamepad.wButtons = (g_controllers[i].old.Gamepad.wButtons ^ g_controllers[i].hold.Gamepad.wButtons) & g_controllers[i].hold.Gamepad.wButtons;
			g_controllers[i].release.Gamepad.wButtons = (g_controllers[i].old.Gamepad.wButtons ^ g_controllers[i].hold.Gamepad.wButtons) & g_controllers[i].old.Gamepad.wButtons;
			g_controllers[i].old = g_controllers[i].hold;
		}
	}
}