#include	"ConsoleWindow.h"

//Debug���[�h�݂̂ŋ@�\����
#ifdef _DEBUG
#include	<stdio.h>

ConsoleWindow	g_ConsoleWindow;

/*! =====================================================================================
@brief	�R���X�g���N�^
@param	void
====================================================================================== */
ConsoleWindow::ConsoleWindow() {

	//�R���\�[���쐬
	AllocConsole();

	//�W�����o�͂̊��蓖��
	FILE*	_fp;
	freopen_s(&_fp, "CONIN$", "r", stdin);		 // �W�����͂̊��蓖��
	freopen_s(&_fp, "CONOUT$", "w", stdout);	 // �W���o�͂̊��蓖��

	HANDLE	_hStdIn = GetStdHandle(STD_INPUT_HANDLE);	 //�W�����̓n���h���̎擾
	HANDLE	_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);	 //�W�����̓n���h���̎擾

	//�E�B���h�E�^�C�g�����Z�b�g
	SetConsoleTitleA("ConsoleWindow");
}

/*! =====================================================================================
@brief	�f�X�g���N�^
@param	void
====================================================================================== */
ConsoleWindow::~ConsoleWindow() {
	//�R���\�[���E�B���h�E���
	FreeConsole();
}


#endif // _DEBUG