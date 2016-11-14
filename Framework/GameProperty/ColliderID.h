	/*! =====================================================================================
@file		ColliderID.h
@brief		コライダーID：衝突判定が必要な対象の判別に使用する
@author		Takuya Kawakami
@date		2016.04.18	新規作成
====================================================================================== */
#pragma once

typedef	unsigned long long	ColliderIdentifier;
namespace CollisionID
{
	static const unsigned long long	NOT_INITIALIZED = 0x000000000000000000;	//非初期化状態
	static const unsigned long long	TERRAIN			= 0x000000000000000001;	//地形
	static const unsigned long long	PLAYER_BODY		= 0x000000000000000002;	//プレイヤー（体）
	static const unsigned long long	PLAYER_HEAD		= 0x000000000000000004;	//プレイヤー（頭）
	static const unsigned long long	PLAYER_BULLET	= 0x000000000000000008;	//プレイヤー（弾）
	static const unsigned long long	PLAYER_WEAPON	= 0x000000000000000010;	//プレイヤー（武器）
	static const unsigned long long	ENEMY_BODY		= 0x000000000000000020;	//エネミー（体）
	static const unsigned long long	ENEMY_HEAD		= 0x000000000000000040;	//エネミー（頭）
	static const unsigned long long	ENEMY_BULLET	= 0x000000000000000080;	//エネミー（弾）
	static const unsigned long long	ENEMY_WEAPON	= 0x000000000000000100;	//エネミー（武器）
	static const unsigned long long	ITEM_			= 0x000000000000000200;	//アイテム...
}