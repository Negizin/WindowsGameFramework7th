#include "Transform.h"
#include <stack>


/*! =====================================================================================
@fn		�R���X�g���N�^
@param	void
====================================================================================== */
Transform::Transform() :
	m_name(_T("NoName")),
	m_scale(1.0f, 1.0f, 1.0f),
	m_pParent(nullptr) {
}

Transform::Transform(GameObject * const _pParent) :
	m_name(_T("NoName")),
	m_scale(1.0f, 1.0f, 1.0f),
	m_pParent(nullptr) {
	m_pGameObject = _pParent;
}

/*! =====================================================================================
@fn		�R���X�g���N�^
@param	Vector3		position
@param	Quaternion	quaternion
@param	Vector3		scale
====================================================================================== */
Transform::Transform(const Vector3 & _position, const Quaternion & _rotation, const Vector3 & _scale) :
	m_name(_T("NoName")),
	m_position(_position),
	m_rotation(_rotation),
	m_scale(_scale) {
}

/*! =====================================================================================
@fn		�R���X�g���N�^
@param	�s��
====================================================================================== */
Transform::Transform(const Matrix & _matrix) :Transform::Transform() {
	*this = _matrix;
}

/*! =====================================================================================
@fn		�f�X�g���N�^
@param	void
====================================================================================== */
Transform::~Transform() {

}

/*! =====================================================================================
@brief	���W�ړ�
@param	Vector3�F�ړ�����W
@return void
====================================================================================== */
void Transform::SetPosition(const Vector3 & _position) {
	m_position = _position;
}

/*! =====================================================================================
@brief	���s�ړ�
@param	Vector3�F�ړ���
@return void
====================================================================================== */
void Transform::Translate(const Vector3 & _vector) {
	m_position += _vector;
}

/*! =====================================================================================
@brief	����n�ɂ����郍�[�J��Z�����w��̕����Ɍ�����
@param	Vector3�F����
@return void
====================================================================================== */
void Transform::LookDirection(const Vector3 & _direction) {
}

/*! =====================================================================================
@brief	����n�ɂ����郍�[�J��Z�����w��̍��W�̕����Ɍ�����
@param	Vector3�F���W
@return void
====================================================================================== */
void Transform::LookAt(const Vector3 & _point) {
}

/*! =====================================================================================
@brief	�w��̃X�P�[���Ƀ��T�C�Y����
@param	Vector3�F���W
@return void
====================================================================================== */
void Transform::Resize(const Vector3 & _scale) {
	m_scale = _scale;
}

/*! =====================================================================================
@brief	���݂̃X�P�[�����w��̔{���Ŋg�k����
@param	Vector3�F���W
@return void
====================================================================================== */
void Transform::Scaling(const Vector3 & _parameter) {
	m_scale.x *= _parameter.x;	m_scale.y *= _parameter.y;	m_scale.z *= _parameter.z;
}

/*! =====================================================================================
@brief	���[�J���X�P�[���擾
@param	void
@return const Vector3&
====================================================================================== */
const Vector3 & Transform::GetLocalScale() const {
	return m_scale;
}

/*! =====================================================================================
@brief	���[�J�����[�e�[�V�����擾
@param	void
@return const Quaternion &
====================================================================================== */
const Quaternion & Transform::GetLocalRotation() const {
	return m_rotation;
}

/*! =====================================================================================
@brief	���[�J���|�W�V�����擾
@param	void
@return const Vector3&
====================================================================================== */
const Vector3 & Transform::GetLocalPosition() const {
	return m_position;
}

/*! =====================================================================================
@brief	���O�擾
@param	void
@return const tstring&
====================================================================================== */
const tstring & Transform::GetName() const {
	return m_name;
}

/*! =====================================================================================
@brief	�Q�[���I�u�W�F�N�g�擾
@param	void
@return const GameObject*
====================================================================================== */
const GameObject * Transform::GetGameObject() const {
	return m_pGameObject;
}

/*! =====================================================================================
@brief	�e�I�u�W�F�N�gTransform�擾
@param	void
@return const Transform*
====================================================================================== */
Transform * Transform::GetParentTransform() const {
	return nullptr;
}

/*! =====================================================================================
@brief	���[���h�s��擾
@param	void
@return Matrix
====================================================================================== */
Matrix Transform::ToWorldMatrix() {
	Matrix result;
	Transform* temp = this;
	std::stack<Matrix> matStack;
	//�e��H���ă��[�J���s����X�^�b�N�Ɋi�[����
	do {
		matStack.push(temp->ToLocalMatrix());
		temp = temp->GetParentTransform();
	} while (temp != nullptr);

	//�X�^�b�N���烍�[�J���s������o�����[���h�s����v�Z����
	while (matStack.empty() == false) {
		result *= matStack.top();
		matStack.pop();
	}

	return result;
}

/*! =====================================================================================
@brief	���[�J���s��擾
@param	void
@return Matrix
====================================================================================== */
Matrix Transform::ToLocalMatrix() const {
	return Matrix(m_position, m_rotation, m_scale);
}

/*! =====================================================================================
@brief	�Q�[���I�u�W�F�N�g�Z�b�g
@param	GameObject*
@return void
====================================================================================== */
void Transform::SetGameObject(GameObject * _pObject) {
	m_pGameObject = _pObject;
}


/*! =====================================================================================

	�ȉ��@���Z�q����

====================================================================================== */

/*! =====================================================================================
@brief	Transform�ւ�Matrix������Z�q��`
@param	Matrix
@return Transform
====================================================================================== */
Transform & Transform::operator=(const Matrix & m) {
	//�p���R�����o
	Vector3 _axisX(m.m[0][0], m.m[0][1], m.m[0][2]);
	Vector3 _axisY(m.m[1][0], m.m[1][1], m.m[1][2]);
	Vector3 _axisZ(m.m[2][0], m.m[2][1], m.m[2][2]);

	//�X�P�[���l�Z�o
	float _scaleX = _axisX.Length();
	float _scaleY = _axisY.Length();
	float _scaleZ = _axisZ.Length();
	m_scale = Vector3(_scaleX, _scaleY, _scaleZ);

	//�ʒu���o
	m_position = Vector3(m.m[3][0], m.m[3][1], m.m[3][2]);

	//�P�ʉ�]�s��Z�o
	Matrix _rotationMatrix;
	_rotationMatrix.m[0][0] = _axisX.x / _scaleX;
	_rotationMatrix.m[1][0] = _axisX.y / _scaleX;
	_rotationMatrix.m[2][0] = _axisX.z / _scaleX;
	_rotationMatrix.m[0][1] = _axisY.x / _scaleY;
	_rotationMatrix.m[1][1] = _axisY.y / _scaleY;
	_rotationMatrix.m[2][1] = _axisY.z / _scaleY;
	_rotationMatrix.m[0][2] = _axisZ.x / _scaleZ;
	_rotationMatrix.m[1][2] = _axisZ.y / _scaleZ;
	_rotationMatrix.m[2][2] = _axisZ.z / _scaleZ;

	//�N�H�[�^�j�I���擾
	m_rotation = _rotationMatrix.ToQuaternion();

	return *this;
}

/*! =====================================================================================
@brief	Transform * Matrix�@�ώZ���Z�q�I�[�o�[���[�h
@param	Matrix
@return Transform
====================================================================================== */
Transform Transform::operator*(const Matrix & _matrix) {
	Matrix _localMatrix = ToLocalMatrix();
	Transform _result((_localMatrix * _matrix));
	_result.m_name = m_name;
	_result.m_pParent = m_pParent;
	return _result;
}

/*! =====================================================================================
@brief	Transform * Matrix�@�ώZ������Z�q�I�[�o�[���[�h
@param	Matrix
@return Transform
====================================================================================== */
Transform & Transform::operator*=(const Matrix & _matrix) {
	return *this = (*this * _matrix);
}