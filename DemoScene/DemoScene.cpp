#include	"DemoScene.h"

#include	"../Framework/BaseSystem/Private/RenderSystem/RenderSystem.h"
#include	"../Framework/BaseSystem/Private/RenderSystem/ResourceManager/ResourceManager.h"
#include	"../Framework/GameObjectClasses/Camera/Camera.h"
#include	"../Framework/BaseSystem/Private/RenderSystem/Mesh/MeshFactory.h"
#include	"../Framework/BaseSystem/Private/RenderSystem/Mesh/MeshObject.h"
#include	"../Framework/BaseSystem/Private/RenderSystem/SystemResource/DrawQueue.h"

/*! =====================================================================================
@brief	コンストラクタ
@param	void
====================================================================================== */
DemoScene::DemoScene() {
}

/*! =====================================================================================
@brief	デストラクタ
@param	void
====================================================================================== */
DemoScene::~DemoScene() {
}

/*! =====================================================================================
@brief	初期化処理
@param	void
@return void
====================================================================================== */
void DemoScene::Initialize() {

	m_pCamera = new Camera();
	m_pCamera->CreateCBuffer();
	m_objectManager.RegisterObject(m_pCamera);

	ResourceManager::Initialize();
	RenderSystem::LoadRenderSystemFromXML(_T("RenderSystem.rs"));

	MeshFactory	_meshFactory;
	_meshFactory.LoadModelFromFile(_T("Resource/Model/miku/Tda式初音ミク・アペンド_Ver1.00_ボーン未改造.pmx"), _T("miku"));

	MeshObject*	_pMesh = ResourceManager::Find<MeshObject>(_T("miku"));

	for (int i = 0; i < _pMesh->GetGeometryCount(); i++) {
		m_pQueue->Add(_pMesh->GetGeometry(i));
	}

	RenderSystem::SetDrawQue(m_pQueue);

}

/*! =====================================================================================
@brief	更新処理
@param	void
@return void
====================================================================================== */
BaseScene * DemoScene::Update() {
	
	//全ｵﾌﾞｼﾞｪｸﾄの更新処理
	m_objectManager.Update();

	return this;
}

/*! =====================================================================================
@brief	更新処理
@param	void
@return void
====================================================================================== */
