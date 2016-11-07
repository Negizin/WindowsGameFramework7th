#include	"FadeSprite.h"

namespace {
	const	float	FADE_TIME = 1.0f;
}

/*! =====================================================================================
@brief	コンストラクタ
@param	void
====================================================================================== */
FadeSprite::FadeSprite() {
	m_bFirstFrame = true;
	m_bFadeIN = true;
	m_bFadeOUT = false;
	m_timer = 0;
}

/*! =====================================================================================
@brief	デストラクタ
@param	void
====================================================================================== */
FadeSprite::~FadeSprite() {
}

/*! =====================================================================================
@brief	更新処理
@param	void
@return void
====================================================================================== */
void FadeSprite::Update() {

	//シーン開始最初のフレームは、シーンの初期化によりTimerのGetDeltaTimeの値が大きすぎて
	//フェードが正しく機能しない＝一瞬で終わることがあるのでパスする必要がある
	if (m_bFirstFrame == true) {
		m_bFirstFrame = false;
		return;
	}

	//タイマー処理
	m_timer += Timer::GetDeltaTime();
	float	_parameter = (m_timer / FADE_TIME) * Math::PI * 0.5f;

	//フェードイン処理
	if (m_bFadeIN) {
		sinf(_parameter);		//サインカーブで補間（透明から不透明）
		if (m_timer > FADE_TIME) {
			m_bFadeIN = false;	//フェードイン終了
			Activate(false);	//更新・描画OFF
		}
	}

	//フェードアウト処理
	if (m_bFadeOUT) {
		cosf(_parameter);		//コサインカーブで補間（不透明から透明）
		if (m_timer > FADE_TIME) {
			m_bFadeOUT = false;	//フェードアウト終了
			Activate(false);	//更新・描画OFF
		}
	}
}

/*! =====================================================================================
@brief	フェードアウト開始
@param	void
@return void
====================================================================================== */
void FadeSprite::StartFadeOut() {
	if (m_bFadeIN | m_bFadeOUT) {
		return;			//既にフェード中の場合は受け付けない
	}
	m_timer = 0;		//タイマー初期化
	m_bFadeOUT = true;	//フェードアウトON
	Activate(true);		//更新・描画ON
}

/*! =====================================================================================
@brief	フェード状態取得
@param	void
@return bool:フェード中ならばtrueを返す
====================================================================================== */
bool FadeSprite::GetFadingState() const {
	return (m_bFadeIN | m_bFadeOUT);
}