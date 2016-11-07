#include	"TimerSystem.h"
#include	"TimerSystemNS.h"


//無名空間	！！！将来的に外部ファイルからの読み込みへ移行を予定！！！
namespace {
	const	float	FRAME_RATE = 120.0f;					// 最大目標fps(frames/sec)
	const	float	MIN_FRAME_RATE = 60.0f;					// 最低許容fps
	const	float	BEST_TIME = 1.0f / FRAME_RATE;			// fps目標達成達成時の１フレーム間経過時間
	const	float	BORDER_TIME = 1.0f / MIN_FRAME_RATE;	// fps最低時の１フレーム間経過時間
}

/*! =====================================================================================
@brief	コンストラクタ
@param	void
====================================================================================== */
TimerSystem::TimerSystem() {
	m_fixedFrameRateFlg = false;
}

/*! =====================================================================================
@brief	デストラクタ
@param	void
====================================================================================== */
TimerSystem::~TimerSystem() {

}

/*! =====================================================================================
@brief	初期化処理
@param	void
@return HRESULT
====================================================================================== */
HRESULT	TimerSystem::Initialize() {
	if (QueryPerformanceFrequency(&m_timerFreq) == false) {
		return E_FAIL;
	}
	QueryPerformanceCounter(&m_timeStart);
	return S_OK;
}

/*! =====================================================================================
@brief	FPS制御：更新可能ならばtrueを返す
@param	void
@return bool
====================================================================================== */
bool	TimerSystem::ControlFPS() {

	//最終フレームからの経過時間取得
	QueryPerformanceCounter(&m_timeEnd);
	g_deltaTime = (float) (m_timeEnd.QuadPart - m_timeStart.QuadPart) / (float) m_timerFreq.QuadPart;

	if (m_fixedFrameRateFlg == true) {	//固定長フレームレートを目指す

		//目標フレームレートまで猶予がある場合、スリープ
		if (g_deltaTime < BEST_TIME) {
			m_sleepTime = (DWORD) ((BEST_TIME - g_deltaTime) * 1000);
			timeBeginPeriod(1);
			Sleep(m_sleepTime);
			timeEndPeriod(1);
			return false;
		}

		//最低許容フレームレートを達成できていない場合
		if (g_deltaTime > BORDER_TIME) {
			//
			//	パーティクルシステムを自重させるコールとか
			//
		}
	}
	else {	
		//可変長フレームレート。目標レートまで余裕があってもスリープしないが、
		//最大値を無制限にしたところ、PCから異音が発生するようになった。
		//暫定的に固定長の倍に最大値を設定することで、解決した。
		if (g_deltaTime < (BEST_TIME / 2.0f)) {
			m_sleepTime = (DWORD) (((BEST_TIME / 2.0f) - g_deltaTime) * 1000);
			timeBeginPeriod(1);
			Sleep(m_sleepTime);
			timeEndPeriod(1);
			return false;
		}
	}

	//前値更新
	m_timeStart = m_timeEnd;

	return true;
}