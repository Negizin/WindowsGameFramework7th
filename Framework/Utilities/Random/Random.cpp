#include	"Random.h"

/*! =====================================================================================
@brief	�R���X�g���N�^
@param	void
====================================================================================== */
RandomGenerator::RandomGenerator() {
	mt32.seed((int) time(0));
}

/*! =====================================================================================
@brief	�f�X�g���N�^
@param	void
====================================================================================== */
RandomGenerator::~RandomGenerator() {
}

/*! =====================================================================================
@brief	32bit�̗������擾����
@param	void
@return int
====================================================================================== */
int	RandomGenerator::GetRandomValue32bit() {
	return mt32();
}

/*! =====================================================================================
@brief	0.0�`1.0�͈̔͂ŗ������擾����
@param	void
@return float
====================================================================================== */
float	RandomGenerator::GetRandomValuePercent() {
	return (float) mt32() / FLT_MAX;
}

/*! =====================================================================================
@brief	�����œn�����l�͈͓̔��ŗ������擾����
@param	void
@return int
====================================================================================== */
int	RandomGenerator::GetRandomValueRange(int min, int max) {
	std::uniform_int_distribution<int> range(min, max);
	return range(mt32);
}


/*! =====================================================================================
@brief	�����œn�����l�͈͓̔��ŗ������擾����
@param	void
@return float
====================================================================================== */
float	RandomGenerator::GetRandomValueRange(float min, float max) {
	std::uniform_real_distribution<float> range(min, max);
	return range(mt32);
}

/*! =====================================================================================
@brief	�V���O���g���̃C���X�^���X�擾
@param	void
@return RandomGenerator&
====================================================================================== */
RandomGenerator&	RandomGenerator::GetInstance() {
	static	RandomGenerator	m_instance;
	return m_instance;
}