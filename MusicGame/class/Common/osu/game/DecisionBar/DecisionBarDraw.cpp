#include "DecisionBarDraw.h"
#include<DxLib.h>
#include"../../../WindowSize.h"
#include"../Lane/LaneDivision.h"
#include"../NoteSizeRatio.h"
#include"../DecisionTransform.h"
#include"../../../Base/GameCore.h"
#include "../GameDrawIndex.h"
#include"../../Skin/Image/SkinImage.h"
#include"CreateBarBoxData.h"

DecisionBarDraw::DecisionBarDraw(LaneDivisionConstPtr division, DecisionTransformConstPtr data)
{
	image_ = lpSkinImagePtr.GetFirstImage(Beat::SkinImageType::DecisionBar);
	CreateDrawData(division, data);
}

DecisionBarDraw::~DecisionBarDraw()
{
	DeleteGraph(screenHndle);
}


void DecisionBarDraw::Draw()
{
	DrawGraph(0, 0, screenHndle, true);
}

void DecisionBarDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(GameDrawIndex::DecisionBar), shared_from_this());
}

void DecisionBarDraw::CreateDrawData(LaneDivisionConstPtr& division, DecisionTransformConstPtr& data)
{
	auto boxVec = CreateBarBoxData()(division, data);
	auto& windowSize = lpWindowSize->GetSize();
	screenHndle = MakeScreen(windowSize.x, windowSize.y, true);
	auto inScreen = GetDrawScreen();
	SetDrawScreen(screenHndle);
	for (auto& box : boxVec)
	{
		DrawExtendGraph(box.LT.x, box.LT.y, box.RB.x, box.RB.y, image_, true);
	}

	SetDrawScreen(inScreen);
}

