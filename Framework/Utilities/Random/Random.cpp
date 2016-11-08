#include	"Random.h"

/*! =====================================================================================
@brief	コンストラクタ
@param	void
====================================================================================== */
RandomGenerator::RandomGenerator() {
	mt32.seed((int) time(0));
}

/*! =====================================================================================
@brief	デストラクタ
@param	void
====================================================================================== */
RandomGenerator::~RandomGenerator() {
}

/*! =====================================================================================
@brief	32bitの乱数を取得する
@param	void
@return int
====================================================================================== */
int	RandomGenerator::GetRandomValue32bit() {
	return mt32();
}

/*! =====================================================================================
@brief	0.0～1.0の範囲で乱数を取得する
@param	void
@return float
====================================================================================== */
float	RandomGenerator::GetRandomValuePercent() {
	return (float) mt32() / FLT_MAX;
}

/*! =====================================================================================
@brief	引数で渡した値の範囲内で乱数を取得する
@param	void
@return int
====================================================================================== */
int	RandomGenerator::GetRandomValueRange(int min, int max) {
	std::uniform_int_distribution<int> range(min, max);
	return range(mt32);
}


/*! =====================================================================================
@brief	引数で渡した値の範囲内で乱数を取得する
@param	void
@return float
====================================================================================== */
float	RandomGenerator::GetRandomValueRange(float min, float max) {
	std::uniform_real_distribution<float> range(min, max);
	return range(mt32);
}

/*! =====================================================================================
@brief	シングルトンのインスタンス取得
@param	void
@return RandomGenerator&
====================================================================================== */
RandomGenerator&	RandomGenerator::GetInstance() {
	static	RandomGenerator	m_instance;
	return m_instance;
}