#include "DecisionDraw.h"
#include<DxLib.h>
#include<algorithm>
#include"../../../WindowSize.h"
#include"../../Skin/Image/SkinImage.h"
#include"../Lane/LaneDivision.h"
#include"../../../Base/GameCore.h"
#include "../GameDrawIndex.h"
#include "../../../../../_debug/_DebugConOut.h"
#include"DecisionDraw/DecisionDrawUp.h"
#include"DecisionDraw/DecisionDrawRePress.h"
DecisionDraw::DecisionDraw(Beat::HitsDataConstPtr hitsData,Decision::SetDrawFuncPtr drawSetFunc)
{
	drawInterFace_ = new DecisionDrawRePress(hitsData);
	*drawSetFunc = std::bind_front(&DecisionDraw::Create, this);
}

DecisionDraw::~DecisionDraw()
{
	delete drawInterFace_;
}

void DecisionDraw::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	drawInterFace_->Update(delta, input);
}

void DecisionDraw::Draw()
{
	drawInterFace_->Draw();
}

void DecisionDraw::Create(const Beat::Type& type)
{
	drawInterFace_->Create(type);

}


void DecisionDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(GameDrawIndex::Decision), shared_from_this());
}

