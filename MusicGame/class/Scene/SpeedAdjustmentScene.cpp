#include "SpeedAdjustmentScene.h"
#include<DxLib.h>
#include"../Input/SpeedAdjust/CreateSpeedAdjustInput.h"
#include"../Common/osu/SpeedAdjust/SetUp/SetUpSpeedAdjust.h"
#include"../Common/WindowSize.h"
#include "../Input/EnumCast.h"
#include"../Input/SpeedAdjust/SpeedAdjustInput.h"


SpeedAdjustmentScene::SpeedAdjustmentScene(std::unique_ptr<BaseScene> before)
{
    before_ = std::move(before);
	Init();
}

SpeedAdjustmentScene::~SpeedAdjustmentScene()
{
}

void SpeedAdjustmentScene::ProcessInput()
{
	BaseScene::ProcessInput();
	core_->ProcessInput();
}

std::unique_ptr<BaseScene> SpeedAdjustmentScene::Update(std::unique_ptr<BaseScene> inScene)
{
	core_->Update(timer_->GetDeletaTime(),*input_);
	if (input_->GetInputData().at(Cast(SPEEDADJUST::BACK)).oneShot())
	{
		before_->ProcessInput();
		return std::move(before_);
	}
    return inScene;
}

void SpeedAdjustmentScene::DrawOnScreen()
{
	SetDrawScreen(handle_);
	ClearDrawScreen();
	before_->Draw();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256 - (256 / 3));
	auto& size = lpWindowSize->GetSize();
	DrawBox(0, 0, size.x, size.y, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	core_->Draw();

}

void SpeedAdjustmentScene::Init()
{
	timer_ = std::make_unique<LoopTimer>();
	CreateSpeedAdjustInput()(input_);
	core_ = std::make_unique<GameCore>(SetUpSpeedAdjust());
}
