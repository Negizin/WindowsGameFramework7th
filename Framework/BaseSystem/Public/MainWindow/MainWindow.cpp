#include	"MainWindow.h"
#include	"../../../BaseSystem/Private/MainWindow/MainWindowNS.h"

/*! =====================================================================================
@brief	ウィンドウ横幅
@param	void
@return unsigned int
====================================================================================== */
unsigned int MainWindow::GetWindowHeight() {
	return MainWindowNS::WINDOW_HEIGHT;
}

/*! =====================================================================================
@brief	ウィンドウ縦幅
@param	void
@return unsigned int
====================================================================================== */
unsigned int MainWindow::GetWindowWidth() {
	return MainWindowNS::WINDOW_WIDTH;
}
