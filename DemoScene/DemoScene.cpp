#include	"DemoScene.h"

#include	"../Framework/BaseSystem/Private/RenderSystem/RenderSystem.h"
#include	"../Framework/BaseSystem/Private/RenderSystem/ResourceManager/ResourceManager.h"
#include	"../Framework/GameObjectClasses/Camera/Camera.h"
#include	"../Framework/BaseSystem/Private/RenderSystem/Mesh/MeshFactory.h"
#include	"../Framework/BaseSystem/Private/RenderSystem/Mesh/MeshObject.h"
#include	"../Framework/BaseSystem/Private/RenderSystem/SystemResource/DrawQueue.h"

/*! =====================================================================================
@brief	�R���X�g���N�^
@param	void
====================================================================================== */
DemoScene::DemoScene() {
}

/*! =====================================================================================
@brief	�f�X�g���N�^
@param	void
====================================================================================== */
DemoScene::~DemoScene() {
}

/*! =====================================================================================
@brief	����������
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
	_meshFactory.LoadModelFromFile(_T("Resource/Model/miku/Tda�������~�N�E�A�y���h_Ver1.00_�{�[��������.pmx"), _T("miku"));

	MeshObject*	_pMesh = ResourceManager::Find<MeshObject>(_T("miku"));

	for (int i = 0; i < _pMesh->GetGeometryCount(); i++) {
		m_pQueue->Add(_pMesh->GetGeometry(i));
	}

	RenderSystem::SetDrawQue(m_pQueue);

}

/*! =====================================================================================
@brief	�X�V����
@param	void
@return void
====================================================================================== */
BaseScene * DemoScene::Update() {
	
	//�S��޼ު�Ă̍X�V����
	m_objectManager.Update();

	return this;
}

/*! =====================================================================================
@brief	�X�V����
@param	void
@return void
====================================================================================== */
