#include	"Camera.h"
#include	"../../BaseSystem/Private/RenderSystem/RenderSystem.h"
#include	"../../BaseSystem/Public/Render/Render.h"
#include	"../../BaseSystem/Private/RenderSystem/Buffer/CBuffer/CBuffer.h"

/*! =====================================================================================
@fn		�R���X�g���N�^
@param	void
====================================================================================== */
Camera::Camera() {
	m_transform.SetPosition(Vector3(0, 10, -20));
	m_up = Vector3(0, 1, 0);
	m_lookAt = Vector3(0, 10, 0);
	m_aspect = 16.0f / 9.0f;
	m_fov = 45.0f;
	m_near = 0.01f;
	m_far = 1000;
	//RenderSystem::GetDevice()->GetDC()->SetMainCamera(this);
	Render::SetMainCamera(this);
	m_pCBuffer = nullptr;
	m_pCBufferMemory = nullptr;
	CreateCBuffer();
}

/*! =====================================================================================
@fn		�f�X�g���N�^
@param	void
====================================================================================== */
Camera::~Camera() {
	SafeDelete(m_pCBuffer);
	SafeDelete(m_pCBufferMemory);
	Render::SetMainCamera(nullptr);
}

/*! =====================================================================================
@brief	������
@param	Vector3:���_���W
@param	Vector3:����x�N�g��
@param	Vector3:�����_���W
@param	float:�A�X�y�N�g(width/height)
@param	float:fov
@param	float:near
@param	float:far
@return void
====================================================================================== */
bool Camera::Initialize(const Vector3& _eyePos, const Vector3& _up, const Vector3& _lookAt, float aspect, float fov, float _near, float _far) {
	return false;
}

/*! =====================================================================================
@brief	�X�V����
@param	void
@return void
====================================================================================== */
void Camera::Update() {
}


bool Camera::CreateCBuffer() {
	m_pCBufferMemory = new ViewCBuffer;
	UpdateForCBuffer();
	m_pCBuffer = new CBuffer();
	m_pCBuffer->CreateCBuffer(m_pCBufferMemory, sizeof(ViewCBuffer));
	if (m_pCBuffer == nullptr)
		return false;
	m_pCBuffer->SetRegisterIndex(MainCameraCbufferRegisterIndex);
	m_pCBuffer->BindShaderType(SHADER_TYPE::VP_SHADER);
	return true;
}

/*! =====================================================================================
@brief	CBuffer�X�V
@param	void
@return bool
====================================================================================== */
bool Camera::UpdateForCBuffer() {
	if (m_pCBufferMemory == nullptr) {
		return false;
	}

	m_pCBufferMemory->m_worldCameraPos = m_transform.GetLocalPosition();
	m_pCBufferMemory->m_near = m_near;
	m_pCBufferMemory->m_far = m_far;
	m_pCBufferMemory->m_fov = m_fov;

	m_pCBufferMemory->m_viewMatrix = GetViewMatrix().Transposed();
	m_pCBufferMemory->m_invViewMatrix = GetViewMatrix().Inversed().Transposed();

	m_pCBufferMemory->m_projMatrix = GetProjectionMatrix().Transposed();
	m_pCBufferMemory->m_invProjMatrix = GetProjectionMatrix().Inversed().Transposed();

	m_pCBufferMemory->m_viewProjMatrix = GetViewProjMatrix().Transposed();

	m_pCBufferMemory->m_dumy = 0;

	if (m_pCBuffer) {
		RenderSystem::GetDevice()->GetDC()->ChangeCBuffer(m_pCBuffer, m_pCBufferMemory, sizeof(ViewCBuffer));
		RenderSystem::GetDevice()->GetDC()->SetCBuffer(m_pCBuffer);
		//m_pCameraCBuffer->Map(pDev->GetDC(), m_pCBufferMemory, sizeof(ViewCBuffer));
	}
	return true;
}

//CBuffer * Camera::GetCBuffer() const {
//	return nullptr;
//}
//
//Camera::ViewCBuffer * Camera::GetViewCBuffer() const {
//	return nullptr;
//}

/*! =====================================================================================
@brief	�v���W�F�N�V�����s��
@param	void
@return Matrix
====================================================================================== */
Matrix Camera::GetProjectionMatrix() const {
	return	XMMatrixPerspectiveFovLH(
		m_fov * 180 / Math::PI,
		m_aspect,
		m_near,
		m_far);
}

/*! =====================================================================================
@brief	�r���[�s��擾
@param	void
@return Matrix
====================================================================================== */
Matrix Camera::GetViewMatrix() const {
	return	XMMatrixLookAtLH(
		m_transform.GetLocalPosition().ToXMVECTOR(),
		m_lookAt.ToXMVECTOR(),
		m_up.ToXMVECTOR());
}

/*! =====================================================================================
@brief	View * Projection
@param	void
@return Matrix
====================================================================================== */
Matrix Camera::GetViewProjMatrix() const {
	return GetViewMatrix() * GetProjectionMatrix();
}