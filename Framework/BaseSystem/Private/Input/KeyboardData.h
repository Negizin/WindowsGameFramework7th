/*! =====================================================================================
@file		KeyboardData.h
@brief		キーボード入力データ
@author		Takuya Kawakami
@date		2016.11.03 最終更新
====================================================================================== */
#pragma once
#define		WIN32_LEAN_AND_MEAN
#include	<windows.h>

//入力状態取得用マスク(int型では足りないので、enum不可)
namespace KCODE
{
	const unsigned	long long	ESC = 0x000000000000000001;		//Escapeキー
	const unsigned	long long	TAB = 0x000000000000000002;		//Tabeキー
	const unsigned	long long	SHIFT_L = 0x000000000000000004;	//LSHIFTキー
	const unsigned	long long	CTRL_L = 0x000000000000000008;	//LSHIFTキー
	const unsigned	long long	ALT_L = 0x000000000000000010;	//左altキー
	const unsigned	long long	SPACE = 0x000000000000000020;	//スペース
	const unsigned	long long	BS = 0x000000000000000040;		//BackSpaceキー
	const unsigned	long long	ENTER = 0x000000000000000080;	//Enterキー
	const unsigned	long long	SHIFT_R = 0x000000000000000100;	//RSHIFTキー
	const unsigned	long long	LEFT = 0x000000000000000200;	//←
	const unsigned	long long	UP = 0x000000000000000400;		//↑
	const unsigned	long long	RIGHT = 0x000000000000000800;	//→
	const unsigned	long long	DOWN = 0x000000000000001000;	//↓
	const unsigned	long long	NUMP_0 = 0x000000000000002000;	//テンキー0
	const unsigned	long long	NUMP_1 = 0x000000000000004000;	//テンキー1
	const unsigned	long long	NUMP_2 = 0x000000000000008000;	//テンキー2
	const unsigned	long long	NUMP_3 = 0x000000000000010000;	//テンキー3
	const unsigned	long long	NUMP_4 = 0x000000000000020000;	//テンキー4
	const unsigned	long long	NUMP_5 = 0x000000000000040000;	//テンキー5
	const unsigned	long long	NUMP_6 = 0x000000000000080000;	//テンキー6
	const unsigned	long long	NUMP_7 = 0x000000000000100000;	//テンキー7
	const unsigned	long long	NUMP_8 = 0x000000000000200000;	//テンキー8
	const unsigned	long long	NUMP_9 = 0x000000000000400000;	//テンキー9
	const unsigned	long long	NUM_0 = 0x000000000000800000;	//0
	const unsigned	long long	NUM_1 = 0x000000000001000000;	//1
	const unsigned	long long	NUM_2 = 0x000000000002000000;	//2
	const unsigned	long long	NUM_3 = 0x000000000004000000;	//3
	const unsigned	long long	NUM_4 = 0x000000000008000000;	//4
	const unsigned	long long	NUM_5 = 0x000000000010000000;	//5
	const unsigned	long long	NUM_6 = 0x000000000020000000;	//6
	const unsigned	long long	NUM_7 = 0x000000000040000000;	//7
	const unsigned	long long	NUM_8 = 0x000000000080000000;	//8
	const unsigned	long long	NUM_9 = 0x000000000100000000;	//9
	const unsigned	long long	A = 0x000000000200000000;		//A
	const unsigned	long long	B = 0x000000000400000000;		//B
	const unsigned	long long	C = 0x000000000800000000;		//C
	const unsigned	long long	D = 0x000000001000000000;		//D
	const unsigned	long long	E = 0x000000002000000000;		//E
	const unsigned	long long	F = 0x000000004000000000;		//F
	const unsigned	long long	G = 0x000000008000000000;		//G
	const unsigned	long long	H = 0x000000010000000000;		//H
	const unsigned	long long	I = 0x000000020000000000;		//I
	const unsigned	long long	J = 0x000000040000000000;		//J
	const unsigned	long long	K = 0x000000080000000000;		//K
	const unsigned	long long	L = 0x000000100000000000;		//L
	const unsigned	long long	M = 0x000000200000000000;		//M
	const unsigned	long long	N = 0x000000400000000000;		//N
	const unsigned	long long	O = 0x000000800000000000;		//O
	const unsigned	long long	P = 0x000001000000000000;		//P
	const unsigned	long long	Q = 0x000002000000000000;		//Q
	const unsigned	long long	R = 0x000004000000000000;		//R
	const unsigned	long long	S = 0x000008000000000000;		//S
	const unsigned	long long	T = 0x000010000000000000;		//T
	const unsigned	long long	U = 0x000020000000000000;		//U
	const unsigned	long long	V = 0x000040000000000000;		//V
	const unsigned	long long	W = 0x000080000000000000;		//W
	const unsigned	long long	X = 0x000100000000000000;		//X
	const unsigned	long long	Y = 0x000200000000000000;		//Y
	const unsigned	long long	Z = 0x000400000000000000;		//Z
}

struct KEYBOARD_STATE {
	 unsigned	long long	 old;		//前フレームでの入力状態
	 unsigned	long long	 hold;		//現在の入力状態
	 unsigned	long long	 trigger;	//トリガー判定用（押したフレーム）
	 unsigned	long long	 release;	//リリース判定用（離したフレーム）
};

//仮想キーコード追記
#define VK_0	(0x0030)
#define VK_1	(0x0031)
#define VK_2	(0x0032)
#define VK_3	(0x0033)
#define VK_4	(0x0034)
#define VK_5	(0x0035)
#define VK_6	(0x0036)
#define VK_7	(0x0037)
#define VK_8	(0x0038)
#define VK_9	(0x0039)

#define	VK_A	(0x0041)	
#define VK_B	(0x0042)
#define VK_C	(0x0043)
#define VK_D	(0x0044)
#define VK_E	(0x0045)
#define VK_F	(0x0046)
#define VK_G	(0x0047)
#define VK_H	(0x0048)
#define VK_I	(0x0049)
#define VK_J	(0x004a)
#define VK_K	(0x004b)
#define VK_L	(0x004c)
#define VK_M	(0x004d)
#define VK_N	(0x004e)
#define VK_O	(0x004f)
#define	VK_P	(0x0050)	
#define	VK_Q	(0x0051)	
#define VK_R	(0x0052)
#define VK_S	(0x0053)
#define VK_T	(0x0054)
#define VK_U	(0x0055)
#define VK_V	(0x0056)
#define VK_W	(0x0057)
#define VK_X	(0x0058)
#define VK_Y	(0x0059)
#define VK_Z	(0x005a)