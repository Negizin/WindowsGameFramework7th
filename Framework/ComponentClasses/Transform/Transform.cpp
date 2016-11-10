#include "Transform.h"

/*! =====================================================================================
@fn		コンストラクタ
@param	void
====================================================================================== */
Transform::Transform() :
	m_name(_T("NoName")),
	m_scale(1.0f, 1.0f, 1.0f),
	m_pGameObject(nullptr),
	m_pParent(nullptr) {
}

/*! =====================================================================================
@fn		コンストラクタ
@param	Vector3		position
@param	Quaternion	quaternion
@param	Vector3		scale
====================================================================================== */
Transform::Transform(const Vector3 & _position, const Quaternion & _rotation, const Vector3 & _scale = Vector3::one) :
	m_name(_T("NoName")),
	m_pGameObject(m_pGameObject),
	m_position(_position),
	m_rotation(_rotation),
	m_scale(_scale) {
}

/*! =====================================================================================
@fn		コンストラクタ
@param	行列
====================================================================================== */
Transform::Transform(const Matrix & _matrix) :Transform::Transform() {
	*this = _matrix;
}

/*! =====================================================================================
@fn		デストラクタ
@param	void
====================================================================================== */
Transform::~Transform() {

}

/*! =====================================================================================
@brief	瞬間移動
@param	Vector3：移動先座標
@return void
====================================================================================== */
void Transform::Teleport(const Vector3 & _position) {
	m_position = _position;
}

/*! =====================================================================================
@brief	平行移動
@param	Vector3：移動量
@return void
====================================================================================== */
void Transform::Translate(const Vector3 & _vector) {
	m_position += _vector;
}

/*! =====================================================================================
@brief	左手系におけるローカルZ軸を指定の方向に向ける
@param	Vector3：方向
@return void
====================================================================================== */
void Transform::LookDirection(const Vector3 & _direction) {
}

/*! =====================================================================================
@brief	左手系におけるローカルZ軸を指定の座標の方向に向ける
@param	Vector3：座標
@return void
====================================================================================== */
void Transform::LookAt(const Vector3 & _point) {
}

/*! =====================================================================================
@brief	指定のスケールにリサイズする
@param	Vector3：座標
@return void
====================================================================================== */
void Transform::Resize(const Vector3 & _scale) {
	m_scale = _scale;
}

/*! =====================================================================================
@brief	現在のスケールを指定の倍率で拡縮する
@param	Vector3：座標
@return void
====================================================================================== */
void Transform::Scaling(const Vector3 & _parameter) {
	m_scale.x *= _parameter.x;	m_scale.y *= _parameter.y;	m_scale.z *= _parameter.z;
}

/*! =====================================================================================
@brief	ローカルスケール取得
@param	void
@return const Vector3&
====================================================================================== */
const Vector3 & Transform::GetLocalScale() const {
	return m_scale;
}

/*! =====================================================================================
@brief	ローカルローテーション取得
@param	void
@return const Quaternion &
====================================================================================== */
const Quaternion & Transform::GetLocalRotation() const {
	return m_rotation;
}

/*! =====================================================================================
@brief	ローカルポジション取得
@param	void
@return const Vector3&
====================================================================================== */
const Vector3 & Transform::GetLocalPosition() const {
	return m_position;
}

/*! =====================================================================================
@brief	名前取得
@param	void
@return const tstring&
====================================================================================== */
const tstring & Transform::GetName() const {
	return m_name;
}

/*! =====================================================================================
@brief	ゲームオブジェクト取得
@param	void
@return const GameObject*
====================================================================================== */
const GameObject * Transform::GetGameObject() const {
	return m_pGameObject;
}

/*! =====================================================================================
@brief	親オブジェクトTransform取得
@param	void
@return const Transform*
====================================================================================== */
const Transform * Transform::GetParentTransform() const {
	return nullptr;
}

/*! =====================================================================================
@brief	ワールド行列取得
@param	void
@return Matrix
====================================================================================== */
Matrix Transform::ToWorldMatrix() const {
	return Matrix();
}

/*! =====================================================================================
@brief	ローカル行列取得
@param	void
@return Matrix
====================================================================================== */
Matrix Transform::ToLocalMatrix() const {
	return Matrix(m_position, m_rotation, m_scale);
}

/*! =====================================================================================
@brief	ゲームオブジェクトセット
@param	GameObject*
@return void
====================================================================================== */
void Transform::SetGameObject(GameObject * _pObject) {
	m_pGameObject = _pObject;
}


/*! =====================================================================================

	以下　演算子実装

====================================================================================== */

/*! =====================================================================================
@brief	TransformへのMatrix代入演算子定義
@param	Matrix
@return Transform
====================================================================================== */
Transform & Transform::operator=(const Matrix & m) {
	//姿勢３軸抽出
	Vector3 _axisX(m.m[0][0], m.m[0][1], m.m[0][2]);
	Vector3 _axisY(m.m[1][0], m.m[1][1], m.m[1][2]);
	Vector3 _axisZ(m.m[2][0], m.m[2][1], m.m[2][2]);

	//スケール値算出
	float _scaleX = _axisX.Length();
	float _scaleY = _axisY.Length();
	float _scaleZ = _axisZ.Length();
	m_scale = Vector3(_scaleX, _scaleY, _scaleZ);

	//位置抽出
	m_position = Vector3(m.m[3][0], m.m[3][1], m.m[3][2]);

	//単位回転行列算出
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

	//クォータニオン取得
	m_rotation = _rotationMatrix.ToQuaternion();

	return *this;
}

/*! =====================================================================================
@brief	Transform * Matrix　積算演算子オーバーロード
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
@brief	Transform * Matrix　積算代入演算子オーバーロード
@param	Matrix
@return Transform
====================================================================================== */
Transform & Transform::operator*=(const Matrix & _matrix) {
	return *this = (*this * _matrix);
}