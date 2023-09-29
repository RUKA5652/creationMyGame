#include "LoopTimer.h"
#include <iostream>

LoopTimer::LoopTimer()
{
	SetUpDeletaTime();
}

void LoopTimer::SetUpDeletaTime()
{
	//各種初期化
	deltaTime_ = 0;
	Reset();
}

DeletaTimeConst& LoopTimer::GetDeletaTime() const
{
	return deltaTime_;
}


void LoopTimer::UpdateDelta()
{
	endTime = std::chrono::system_clock::now();
	//起点の時間と終わりの時間の差分を作成
	deltaTime_ =static_cast<DeletaTime>((std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()));

	startTime = endTime;
}

void LoopTimer::Reset()
{
	//スタートとエンドを揃えて次の計測に備える
	startTime = std::chrono::system_clock::now();
	endTime = startTime;
}

