/*! =====================================================================================
@file		Random.h
@brief		�����Z���k�E�c�C�X�^����������
@author		Takuya Kawakami
@date		2016.02.02	�V�K�쐬
====================================================================================== */
#pragma once
#include	<random>
#include	<time.h>

/* �Q�[���������Ŏg�p����Ƃ��́A�t�@�C�������ɂ���}�N�����g�p���Ă��������@*/

class RandomGenerator {
public:
	/*! =====================================================================================
	@brief	32bit�̗������擾����
	@param	void
	@return int
	====================================================================================== */
	int	GetRandomValue32bit();

	/*! =====================================================================================
	@brief	0.0�`1.0�͈̔͂ŗ������擾����
	@param	void
	@return float
	====================================================================================== */
	float	GetRandomValuePercent() { return (float) mt32() / FLT_MAX; }

	/*! =====================================================================================
	@brief	�����œn�����l�͈͓̔��ŗ������擾����
	@param	void
	@return int
	====================================================================================== */
	int	GetRandomValueRange(int min, int max);

	/*! =====================================================================================
	@brief	�����œn�����l�͈͓̔��ŗ������擾����
	@param	void
	@return float
	====================================================================================== */
	float	GetRandomValueRange(float min, float max);

private:
	RandomGenerator();
	~RandomGenerator();

	//�V���O���g��
	static RandomGenerator& GetInstance();
	RandomGenerator(const RandomGenerator &singleton) {}	// �R�s�[�R���X�g���N�^�֎~
	void operator=(const RandomGenerator& singleton) {}		// ������Z�q�֎~

	//�����Z���k�c�C�X�^����������
	std::mt19937	mt32;
};


//����������ւ̃A�N�Z�X�p�}�N��
#define	Random Singleton<RandomGenerator>::GetInstance()