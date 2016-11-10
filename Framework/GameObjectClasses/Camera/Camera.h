/*! =====================================================================================
@file		Camera.h
@brief		�J�������N���X
@author		Takuya Kawakami
@date		2016.11.10	�ŏI�X�V
====================================================================================== */
#pragma once
#include	"../GameObject.h"
class CBuffer;

class Camera :public GameObject {
public:
	Camera();
	virtual ~Camera();
	static const int MainCameraCbufferRegisterIndex = 7;
	
	//
	bool Initialize(const Vector3& _eyePos, const Vector3& _up, const Vector3& _lookAt,float aspect, float fov, float _near, float _far);
	void Update();

	bool UpdateForCBuffer();


	//
	Matrix	GetProjectionMatrix()const;
	Matrix	GetViewMatrix()const;
	Matrix	GetViewProjMatrix()const;

	struct ViewCBuffer {
		Matrix	m_viewMatrix;
		Matrix	m_projMatrix;
		Matrix	m_invViewMatrix;
		Matrix	m_invProjMatrix;
		Matrix	m_viewProjMatrix;

		Vector4	m_worldCameraPos;
		//TsFloat4 m_projRaito;

		float	m_near;
		float	m_far;
		float	m_fov;
		float	m_dumy;
	};

protected:
	Vector3	m_lookAt;
	Vector3 m_up;
	float	m_aspect;
	float	m_fov;
	float	m_near;
	float	m_far;
	CBuffer*		m_pCBuffer;
	ViewCBuffer*	m_pCBufferMemory;
};
