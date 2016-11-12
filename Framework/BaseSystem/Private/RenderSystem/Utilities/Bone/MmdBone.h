#pragma once

#include <Windows.h>
#include <vector>
#include	"../../../../../Utilities/Math/Math.h"

using namespace DirectX;

struct MMDBone {
	int id;						// ボーンID（通し番号）
	std::string name;			// ボーン名
	unsigned char type;			// ボーンタイプ (MMDの場合 0:回転 1:回転と移動 2:IK 3:不明 4:IK影響下 5:回転影響下 6:IK接続先 7:非表示 8:捻り 9:回転運動 )
	MMDBone* parent;			// 親ボーン
	MMDBone* firstChild;		// 第1子ボーン
	MMDBone* sibling;			// 次の兄弟ボーン
	Matrix initMat;				// 初期姿勢行列(ボーンローカル座標系)
	Matrix boneMat;				// ボーン行列(ボーンローカル座標系)
	Matrix offsetMat;			// ボーンオフセット行列(モデルローカル座標系)

	MMDBone() :type(), id(), parent(), firstChild(), sibling() {	// コンストラクタ
		memcpy(&initMat, &XMMatrixIdentity(), sizeof(XMFLOAT4));
		memcpy(&offsetMat, &XMMatrixIdentity(), sizeof(XMFLOAT4));
		memcpy(&boneMat, &XMMatrixIdentity(), sizeof(XMFLOAT4));
	};

	Matrix GetModelLocalBoneMat();
	Matrix XMGetModelLocalBoneMat();
	Vector4 GetModelLocalPosition();
};


struct MMDIKBone {
	WORD	boneIndex;			///< IKボーン番号（インデックス）
	WORD	effectorBoneIndex;	///< IKボーンの位置に、このボーンを一致させるようにIK処理が行われる
	BYTE	chainLength;		///< IKチェーンの長さ
	WORD	numIterations;		///< 再帰演算回数
	FLOAT	controlWeight;		///< ボーンの単位制限角 1.0->4.0[rad]. また「ひざ」という名前のボーンはX軸方向にしか動かない制限がある
	std::vector<USHORT>  childBoneIndexVector;	///< 子供IKのインデックスvector
};


// キーフレームアニメーションデータ
struct KeyFrame {
	std::string boneName;		// ボーン名
	unsigned long frameNo;	// フレーム番号
	Vector3 position;	// 位置
	Vector4 rotation;// 回転
	Vector2 interpolation_x[2];	// position.xのベジェ補完パラメータ
	Vector2 interpolation_y[2];	// position.yのベジェ補完パラメータ
	Vector2 interpolation_z[2];	// position.zのベジェ補完パラメータ
	Vector2 interpolation_r[2];	// rotationのベジェ補完パラメータ
	bool operator < (const KeyFrame &k) const {	// フレーム番号でソートするための比較演算子
		return frameNo < k.frameNo;
	}
};
