#pragma once
/**********************************************************************
/*		インクルード
/*
*********************************************************************/
#include <vector>
#include <list>


#include "../../Math/Bone/MmdBone.h"

/**********************************************************************
/*		ライブラリ
/*
*********************************************************************/
using namespace DirectX;
/**********************************************************************
/*		マクロ、定数定義
/*
*********************************************************************/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*   CVmdController
*
*   @brief VMDコントローラクラス
*   @author  Miyahara Satoshi
*   \date    2016/5/16　新規作成
*
*   \Update
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Vmd
{
public:
#pragma pack(push,1)	//アラインメント制御をオフ
	/*!-----------------------------------------------------------
	//	@struct	VMDHeader
	//	@brief	VMD構造体ヘッダ
	//	@author	Tatsunori Aoyama
	//	@date	2014/10/03
	------------------------------------------------------------*/
	struct Header
	{
		char vmdHeader[30];
		char vmdModelName[20];
	};

	/*!-----------------------------------------------------------
	//	@struct	VMDMotion
	//	@brief	VMD構造体
	//	@author	Tatsunori Aoyama
	//	@date	2014/10/03
	------------------------------------------------------------*/
	struct Motion
	{
		char			boneName[15];		///< 動かすボーンの名前
		unsigned long	frameNo;			///< フレーム番号
		float			location[3];		///< 移動量
		float			localRotation[4];		///< モデルローカル座標系
		unsigned char	interpolation[64];	///<[4][4][4]モーション補間形式
	};

#pragma pack(pop)
};

class VmdLoader{



};


class VmdMotion{
private:
	int time = 0;							// 時間
	int MaxFrame = 0;						//モーションにかかるフレーム
	int cooltime = 30;
	std::vector<MMDBone>* bones;					//ボーン配列のポインタ
	std::vector<MMDIKBone>* pmdIkData;				//IKボーン配列のポインタ
	std::vector<Vector4> boneRot;					// 現在のボーンの回転
	std::vector<Vector3> bonePos;					// 現在のボーンの位置
	std::vector<std::list<KeyFrame>> keyFrames;				// ボーンごとにキーフレームをリストとしてもつ
	std::vector<std::list<KeyFrame>::iterator> ite_keyFrames;	// キーフレームのイテレータ

public:
	VmdMotion(void){};//コンストラクタ
	~VmdMotion(){};

	void UpdateBoneMatrix();				// キーフレームデータを元にボーン行列を更新
	void AdvanceTime();
	void Update();
	void SetBonePos(std::vector<Vector3> bonepos);
	void SetBoneRot(std::vector<Vector4> boneros);
	void SetBone(std::vector<MMDBone> &_bone, std::vector<MMDIKBone>& _pmd);
	bool LoadVmdFile(LPCTSTR filename);
private:
	void UpdateIK(const MMDIKBone&);		// IKボーン影響下ボーンの行列を更新

public:
	std::vector<Vector3>* GetBonePos(){ return &bonePos; }
	std::vector<Vector4>* GetBoneRot(){ return &boneRot; }
	std::vector<MMDBone>* GetBone(){ return bones; }
};