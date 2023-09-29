#include "ScoreDraw.h"
#include"../../../Base/GameCore.h"
#include "../GameDrawIndex.h"
#include<DxLib.h>
#include "../../Skin/Image/SkinImage.h"





ScoreDraw::ScoreDraw(Beat::HitsDataPtr hitdata)
{
	hitdata_ = hitdata;
	const auto& data = lpSkinImagePtr.GetAllImage(Beat::SkinImageType::num);
	for (int i = 0; i < data.size(); i++)
	{
		numImage_[i] = data[i];
	}

	GetGraphSize(numImage_[0], &imageSize_.x, &imageSize_.y);
	maxCnt_ = 1;
	for (int i = 10; Beat::maxScore % i != Beat::maxScore; i *= 10)
	{
		maxCnt_++;
	}

	digits_ = maxCnt_ * imageSize_.x;

}

void ScoreDraw::Draw()
{
	auto numData = static_cast<int>(std::round(hitdata_->score));
	int size = 1;
	for (int i = 10; numData % i != numData; i *= 10)
	{
		size++;
	}
	int cnt = 1;
	
	for (int num = numData % 10; cnt <= maxCnt_; numData /= 10, num = numData % 10 , cnt++)
	{
		if (cnt > size)
		{
			num = 0;
		}
		DrawGraph(imageSize_.x * (maxCnt_ - cnt) /*‚¸‚ç‚·—Ê*/, 0, numImage_[num], true);
		
	}

}

void ScoreDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(GameDrawIndex::Score), shared_from_this());
}
