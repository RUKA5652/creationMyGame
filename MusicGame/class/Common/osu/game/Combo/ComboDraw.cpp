#include "ComboDraw.h"
#include"../../../Base/GameCore.h"
#include<DxLib.h>
#include<string>
#include"../../Skin/Image/SkinImage.h"
#include"../../../WindowSize.h"
#include "../GameDrawIndex.h"
#include"../../../../AnimCurve/animCurve.h"
#include "../../../../../_debug/_DebugConOut.h"


constexpr Timer::DeletaTime animTime = 400;

ComboDraw::ComboDraw(Beat::HitsDataConstPtr hitdata)
{
	hitdata_ = std::move(hitdata);
	Init();
}

void ComboDraw::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	if (beforeCnt_ != hitdata_->combo)
	{
		beforeCnt_ = hitdata_->combo;
		animStime_ = delta;
		//TRACE("Start\n");
	}
	float time = static_cast<float>(delta - animStime_);
	time = time / animTime;
	auto t = MoveOutIn(time ,8);
	exSize_ = std::lerp(1.5f, 1.0f, t);
	//TRACE("%f:%f\n", exSize_,time);
}

void ComboDraw::Draw()
{
	auto inScreen = GetDrawScreen();
	SetDrawScreen(screen_);
	ClearDrawScreen();
	/** //•¶Žš—ñ‚É’¼‚·‚à‚Ì
	auto numString = std::to_string(hitdata_->combo);

	DrawString(0, 500, std::to_string(hitdata_->combo).c_str(), 0xffffff);
	
	auto& winSize = lpWindowSize->GetSize();

	auto size = static_cast<int>(numString.size());

	auto maxSize = size * imageSize_.x;
	int cnt = 0;
	for (auto numChar : numString)
	{
		DrawGraph(winSize.x/2 - maxSize/2 + imageSize_.x * cnt++, winSize.y/2, numImage_[std::atoi(&numChar)], true);
	}
	/*/ //•¶Žš•ÏŠ·‚µ‚È‚¢ŽÀ‘•

	auto& winSize = lpWindowSize->GetSize();
	auto numData = hitdata_->combo;
	int size = 1;
	for (int i = 10; numData % i != hitdata_->combo; i *= 10)
	{
		size++;
	}	
	int cnt = 0;
	auto maxSize = size * imageSize_.x;
	for (int num = numData % 10 ; cnt < size; numData/=10 ,num = numData % 10)
	{
		DrawGraph( (winSize.x - (maxSize) )/ 2 /*center*/  + imageSize_.x *(size - ++cnt) /*‚¸‚ç‚·—Ê*/, winSize.y / 2, numImage_[num], true);
	}

	/**/
	SetDrawScreen(inScreen);
	auto center = screenSize_ / 2;
	auto drawSize = center * exSize_;
	DrawExtendGraphF(center.x - drawSize.x, center.y - drawSize.y, center.x + drawSize.x, center.y + drawSize.y, screen_, true);
	TRACE("%f:%f\n", drawSize.x, drawSize.y);
}

void ComboDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(GameDrawIndex::Combo), shared_from_this());
}

void ComboDraw::Init()
{
	const auto& data = lpSkinImagePtr.GetAllImage(Beat::SkinImageType::num);
	for (int i = 0; i < data.size(); i++)
	{
		numImage_[i] = data[i];
	}

	GetGraphSize(numImage_[0], &imageSize_.x, &imageSize_.y);

	auto& size = lpWindowSize->GetSize();
	screenSize_ = { size.x,size.y };
	screen_ = MakeScreen(size.x, size.y, true);

	animStime_ = 0;
	beforeCnt_ = 0;
}
