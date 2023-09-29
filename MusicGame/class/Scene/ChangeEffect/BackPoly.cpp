#define NOMINMAX
#include "BackPoly.h"
#include"../../Common/WindowSize.h"

BackPoly::BackPoly(FLOAT4& size)
	:EffectPoly(size)
{
	Init();
}

void BackPoly::Update(Timer::DeletaTimeConst& time)
{
	if (endFlag_)
	{
		return;
	}
	moveTime_ += time;
	func_[state_]();
}

void BackPoly::Init()
{
	state_ = State::MoveIpda;
	func_ = {
		{State::MoveIpda,std::bind(&BackPoly::MoveIpdaSize,this)},
		{State::MoveScreen,std::bind(&BackPoly::MoveScreen,this)},
	};
	screenSize_ = {0,0,0,0};

}

void BackPoly::Scale(FLOAT4& size, float t)
{
	auto& windSize = lpWindowSize->GetSize();
	poly[0].pos.x = std::lerp(poly[0].pos.x, size.x, t);
	poly[0].pos.y = std::lerp(poly[0].pos.y, size.y, t);

	poly[1].pos.x = std::lerp(poly[1].pos.x, windSize.x - size.z, t);
	poly[1].pos.y = std::lerp(poly[1].pos.y, size.y, t);

	poly[2].pos.x = std::lerp(poly[2].pos.x, size.x, t);
	poly[2].pos.y = std::lerp(poly[2].pos.y, windSize.y - size.w, t);

	poly[3].pos.x = std::lerp(poly[3].pos.x, windSize.x - size.z, t);
	poly[3].pos.y = std::lerp(poly[3].pos.y, windSize.y - size.w, t);
}

void BackPoly::MoveIpdaSize()
{
	auto t = std::min(moveTime_ / 1000.0f, 1.0f);
	Scale(ipadData_, t);
	if (moveTime_ >= 1250 + 750 + 300.0f)
	{
		state_ = State::MoveScreen;
		moveTime_ = 0;
	}
}

void BackPoly::MoveScreen()
{
	auto t = std::min(moveTime_ / 1000.0f, 1.0f);
	Scale(screenSize_, t);
	if (moveTime_ >= 1000.0f)
	{
		endFlag_ = true;
	}

}
