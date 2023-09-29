#include "StraightLaneDraw.h"
#include<DxLib.h>
#include"../../../../WindowSize.h"
#include"../LaneDivision.h"
#include"../../../../Base/GameCore.h"
#include"../../../Skin/Image/SkinImage.h"
#include "../../GameDrawIndex.h"

StraightLaneDraw::StraightLaneDraw(LaneDivisionConstPtr&& divData)
	:StraightLaneDraw(divData)
{
}

StraightLaneDraw::StraightLaneDraw(LaneDivisionConstPtr& divData)
{
	Init();
	CreateMultipleLane(divData);
}

StraightLaneDraw::~StraightLaneDraw()
{
	DeleteGraph(multipleLaneImage_);
}

void StraightLaneDraw::Draw()
{
	DrawGraph(0, 0, multipleLaneImage_,true);
	//DrawModiGraph(100, 0, 600, 0, windowSize.x, windowSize.y, 0, windowSize.y, multipleLaneImage_, true);
}

void StraightLaneDraw::Init()
{
	multipleLaneImage_ = -1;
	laneNum = 4;
}


void StraightLaneDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(GameDrawIndex::Lane), shared_from_this());
}

void StraightLaneDraw::CreateMultipleLane(LaneDivisionConstPtr& divData)
{
	
	auto& windowSize = lpWindowSize->GetSize();
	multipleLaneImage_ = MakeScreen(windowSize.x, windowSize.y,true);

	int image = lpSkinImagePtr.GetFirstImage(Beat::SkinImageType::Lane);

	auto inScreen = GetDrawScreen();
	SetDrawScreen(multipleLaneImage_);

	for (auto& data : divData->GetBoxVec())
	{
		DrawExtendGraph(data.LT.x, data.LT.y, data.RB.x, data.RB.y, image, true);
	}

	SetDrawScreen(inScreen);

	
}
