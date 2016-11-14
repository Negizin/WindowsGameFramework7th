#include	"Render.h"
#include	"../../Private/RenderSystem/RenderSystemNS.h"
#include	"../../Private/RenderSystem/RenderSystem.h"

/*! =====================================================================================
@brief	メインカメラ設定
@param	Camera*
@return void
====================================================================================== */
void Render::SetMainCamera(Camera * _pMainCamera) {
	RenderSystem::GetDevice()->GetDC()->SetMainCamera(_pMainCamera);
}
