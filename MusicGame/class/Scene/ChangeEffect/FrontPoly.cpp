#define NOMINMAX
#include "FrontPoly.h"
#include "../../Common/WindowSize.h"
#include "../../SoundVolume/SoundVolume.h"

FrontPoly::FrontPoly(FLOAT4& size)
	:EffectPoly(size)
{
	Init();
}

FrontPoly::~FrontPoly()
{
	DeleteSoundMem(soundHandle_);
}

void FrontPoly::Update(Timer::DeletaTimeConst& time)
{
	if (endFlag_)
	{
		return;
	}
	moveTime_ += time;
	func_[state_]();
}

void FrontPoly::Init()
{
	state_ = State::MoveIpda;
	func_ = {
		{State::MoveIpda,std::bind(&FrontPoly::MoveIpdaSize,this)},
		{State::ScaleDown,std::bind(&FrontPoly::MoveScaleDown,this)},
		{State::MoveUp,std::bind(&FrontPoly::MoveUp,this)}
	};

	auto& size = lpWindowSize->GetSize();
	auto sizeX = size.x - ipadData_.x - ipadData_.z;
	auto sizeY = size.y - ipadData_.y - ipadData_.w;

	sizeX = size.x - sizeX / 4;
	sizeY = size.y - sizeY / 4;

	scaleDownSize_ = {
		sizeX/2,
		sizeY/2,
		sizeX / 2,
		sizeY / 2,
	};

	soundHandle_ = LoadSoundMem("resource/skin/transition/move.mp3");
}

void FrontPoly::ScaleDown(FLOAT4& size, float t)
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

void FrontPoly::MoveIpdaSize()
{
	auto t = std::min(moveTime_ / 1000.0f, 1.0f);
	ScaleDown(ipadData_, t);
	if (moveTime_ >= 1250)
	{
		state_ = State::ScaleDown;
		moveTime_ = 0;
	}

}

void FrontPoly::MoveScaleDown()
{
	auto t = std::min(moveTime_ / 500.0f, 1.0f);
	ScaleDown(scaleDownSize_, t);
	if (moveTime_ >= 750)
	{
		state_ = State::MoveUp;
		moveTime_ = 0;
		//PlaySoundMem(soundHandle_, DX_PLAYTYPE_BACK);
		lpVolumeMng.PlaySoundMem(soundHandle_, Sound::Type::SE, DX_PLAYTYPE_BACK);
	}
}

void FrontPoly::MoveUp()
{
	auto sizeY = poly[3].pos.y - poly[0].pos.y;
	auto t = std::min(moveTime_ / 250.0f, 1.0f);
	poly[0].pos.y = std::lerp(poly[0].pos.y, -sizeY , t);

	poly[1].pos.y = std::lerp(poly[1].pos.y, -sizeY, t);

	poly[2].pos.y = std::lerp(poly[2].pos.y, 0, t);

	poly[3].pos.y = std::lerp(poly[3].pos.y,0, t);
	if (moveTime_ >= 250)
	{
		endFlag_ = true;
	}
}

