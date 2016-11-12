/*!-----------------------------------------------------------------/
//@brief	IKBone.h
//
//  IKボーンクラス
//
//@Auther   宮原敏史
//@Date     2016/10/30
//-----------------------------------------------------------------*/
#pragma once

#include	"../Bone/Bone.h"
#include	<Windows.h>
#include	<vector>


struct IKBone {
	WORD	boneIndex;			///< IKボーン番号（インデックス）
	WORD	effectorBoneIndex;	///< IKボーンの位置に、このボーンを一致させるようにIK処理が行われる
	BYTE	chainLength;		///< IKチェーンの長さ
	WORD	numIterations;		///< 再帰演算回数
	FLOAT	controlWeight;		///< ボーンの単位制限角 1.0->4.0[rad]. また「ひざ」という名前のボーンはX軸方向にしか動かない制限がある
	std::vector<USHORT>  childBoneIndexVector;	///< 子供IKのインデックスvector
};