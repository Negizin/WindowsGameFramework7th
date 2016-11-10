#include	"Camera.h"
#include	"../../BaseSystem/Private/RenderSystem/RenderSystem.h"

/*! =====================================================================================
@fn		�R���X�g���N�^
@param	void
====================================================================================== */
Camera::Camera() {
	m_transform.SetPosition(Vector3(0, 10, -30));
	m_up = Vector3(0, 1, 0);
	m_lookAt = Vector3(0, 10, 0);
	m_aspect = 16.0f / 9.0f;
	m_fov = 45.0f;
	m_near = 0.001f;
	m_far = 2000;

}

/*! =====================================================================================
@fn		�f�X�g���N�^
@param	void
====================================================================================== */
Camera::~Camera() {
	SafeDelete(m_pCBuffer);
	SafeDelete(m_pCBufferMemory);
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