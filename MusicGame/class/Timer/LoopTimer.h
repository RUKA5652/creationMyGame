#pragma once
#include <chrono>
#include"Timer.h"


/// <summary>
/// 経過時間計算クラス
/// </summary>
class LoopTimer
{
public:
	LoopTimer();
	virtual ~LoopTimer() {};
	//時間取得
	DeletaTimeConst& GetDeletaTime() const;
	//時間計算
	virtual void UpdateDelta();
	//初期化
	void Reset();

protected:	
	//起点の時間
	std::chrono::system_clock::time_point  startTime;
	//終わりの時間
	std::chrono::system_clock::time_point  endTime;
	//経過時間
	DeletaTime deltaTime_;
private:
	//セットアップ
	void SetUpDeletaTime();
};

using LoopTimerPtr = std::unique_ptr<LoopTimer>;
