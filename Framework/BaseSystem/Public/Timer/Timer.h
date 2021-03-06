/*! =====================================================================================
@file		Timer.h
@brief		タイマーシステムのデータへのアクセスをゲーム実装部に提供するメソッドをまとめた名前空間によるインターフェース
@author		Takuya Kawakami
@date		2016.11.03	新規作成
====================================================================================== */
#pragma once

namespace Timer {

	/*! =====================================================================================
	@brief	直前のフレームから現在のフレーム間に要した時間を取得
	@param	void
	@return float
	====================================================================================== */
	float	GetDeltaTime();

	/*! =====================================================================================
	@brief	時間経過速度を取得（デフォルトでは1.0f）
	@param	void
	@return float
	====================================================================================== */
	float	GetTimeScale();

	/*! =====================================================================================
	@brief	時間経過速度を設定（デフォルトでは1.0f）
	@param	float
	@return void
	====================================================================================== */
	void	SetTimeScale(float	_parameter);
}
