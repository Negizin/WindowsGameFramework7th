	/*! =====================================================================================
@file		ColliderID.h
@brief		�R���C�_�[ID�F�Փ˔��肪�K�v�ȑΏۂ̔��ʂɎg�p����
@author		Takuya Kawakami
@date		2016.04.18	�V�K�쐬
====================================================================================== */
#pragma once

typedef	unsigned long long	ColliderIdentifier;
namespace CollisionID
{
	static const unsigned long long	NOT_INITIALIZED = 0x000000000000000000;	//�񏉊������
	static const unsigned long long	TERRAIN			= 0x000000000000000001;	//�n�`
	static const unsigned long long	PLAYER_BODY		= 0x000000000000000002;	//�v���C���[�i�́j
	static const unsigned long long	PLAYER_HEAD		= 0x000000000000000004;	//�v���C���[�i���j
	static const unsigned long long	PLAYER_BULLET	= 0x000000000000000008;	//�v���C���[�i�e�j
	static const unsigned long long	PLAYER_WEAPON	= 0x000000000000000010;	//�v���C���[�i����j
	static const unsigned long long	ENEMY_BODY		= 0x000000000000000020;	//�G�l�~�[�i�́j
	static const unsigned long long	ENEMY_HEAD		= 0x000000000000000040;	//�G�l�~�[�i���j
	static const unsigned long long	ENEMY_BULLET	= 0x000000000000000080;	//�G�l�~�[�i�e�j
	static const unsigned long long	ENEMY_WEAPON	= 0x000000000000000100;	//�G�l�~�[�i����j
	static const unsigned long long	ITEM_			= 0x000000000000000200;	//�A�C�e��...
}