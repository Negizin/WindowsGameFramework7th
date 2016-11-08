/*! =====================================================================================
@file		Random.h
@brief		メルセンヌ・ツイスタ乱数生成器
@author		Takuya Kawakami
@date		2016.02.02	新規作成
====================================================================================== */
#pragma once
#include	<random>
#include	<time.h>

/* ゲーム実装部で使用するときは、ファイル末尾にあるマクロを使用してください　*/

class RandomGenerator {
public:
	/*! =====================================================================================
	@brief	32bitの乱数を取得する
	@param	void
	@return int
	====================================================================================== */
	int	GetRandomValue32bit();

	/*! =====================================================================================
	@brief	0.0～1.0の範囲で乱数を取得する
	@param	void
	@return float
	====================================================================================== */
	float	GetRandomValuePercent() { return (float) mt32() / FLT_MAX; }

	/*! =====================================================================================
	@brief	引数で渡した値の範囲内で乱数を取得する
	@param	void
	@return int
	====================================================================================== */
	int	GetRandomValueRange(int min, int max);

	/*! =====================================================================================
	@brief	引数で渡した値の範囲内で乱数を取得する
	@param	void
	@return float
	====================================================================================== */
	float	GetRandomValueRange(float min, float max);

private:
	RandomGenerator();
	~RandomGenerator();

	//シングルトン
	static RandomGenerator& GetInstance();
	RandomGenerator(const RandomGenerator &singleton) {}	// コピーコンストラクタ禁止
	void operator=(const RandomGenerator& singleton) {}		// 代入演算子禁止

	//メルセンヌツイスタ乱数生成器
	std::mt19937	mt32;
};


//乱数生成器へのアクセス用マクロ
#define	Random Singleton<RandomGenerator>::GetInstance()