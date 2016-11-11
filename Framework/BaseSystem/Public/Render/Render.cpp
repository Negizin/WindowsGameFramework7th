#include	"Render.h"
#include	"../../Private/RenderSystem/RenderSystemNS.h"

void Render::SetMainCamera(Camera * _pMainCamera) {
	g_pDevice->GetDC()->SetMainCamera(_pMainCamera);
}
