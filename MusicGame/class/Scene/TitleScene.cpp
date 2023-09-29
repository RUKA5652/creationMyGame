#include "TitleScene.h"
#include"../Input/Title/CreateTitleInput.h"
#include"../Common/osu/Title/SetUp/SetUpTitleScene.h"
#include"SelectScene.h"
#include <DxLib.h>
#include "../../_debug/_DebugConOut.h"
#include "../Input/EnumCast.h"

TitleScene::TitleScene(Beat::ReelDataPtr reelData, ReelSound* reelSound)
{
	reelData_ = reelData;
	reelSound_ = reelSound;
	Init();
}

TitleScene::TitleScene()
{	
	reelData_ = std::make_shared<Beat::ReelData>();
	Init();
}

TitleScene::~TitleScene()
{
	//thread_.join();
}

void TitleScene::ProcessInput()
{	
	BaseScene::ProcessInput();
	core_->ProcessInput();
	if (input_->GetInputData().at(Cast(TITLE::BACK)).oneShot())
	{
		std::exit(EXIT_SUCCESS);
	}
}



std::unique_ptr<BaseScene> TitleScene::Update(std::unique_ptr<BaseScene> inScene)
{
	core_->Update(timer_->GetDeletaTime(), *input_);
	if (nextScene_)
	{
		changeEffect_.Update(timer_->GetDeletaTime());
		changeFlag_ = changeEffect_.GetEnd();
	}
	return (nextScene_ && changeFlag_ ? std::move(nextScene_) : std::move(inScene));
}

void TitleScene::Init()
{

	CreateTitleInput()(input_);
	timer_ = std::make_unique<LoopTimer>();
	core_ = std::make_unique<GameCore>(SetUpTitleScene(reelSound_,reelData_,
	std::make_shared<std::function<void(void)>>(std::bind_front(&TitleScene::ChengeSelect,this))));
}

void TitleScene::ChengeSelect()
{
	if (/*thread_.joinable() || */nextScene_)
	{
		return;
	}
	nextScene_ = std::make_unique<SelectScene>(reelData_, reelSound_);
}

void TitleScene::DrawOnScreen()
{
	SetDrawScreen(handle_);
	ClearDrawScreen();
	core_->Draw();
	if (nextScene_)
	{
		changeEffect_.Draw(this, nextScene_.get());
	}
}
