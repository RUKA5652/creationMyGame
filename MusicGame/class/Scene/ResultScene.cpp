#include "ResultScene.h"
#include"../Input/Result/CreateResultInput.h"
#include"../Common/osu/Result/SetUp/SetUpResultScene.h"
#include"../Common/osu/Skin/Image/SkinImage.h"
#include <DxLib.h>
#include"GameScene.h"
#include"SelectScene.h"
#include"../Common/osu/HistoryScore/HistoryScoreLoad.h"
#include"../Common/osu/HistoryScore/HistoryScoreSave.h"

ResultScene::ResultScene(int sortIndex, int groupIndex, Beat::ReelSortType type,const std::string& filePass,Beat::ResultDataConstPtr result)
{
	sortIndex_ = sortIndex;
	groupIndex_ = groupIndex;
	type_ = type;

	timer_ = std::make_unique<LoopTimer>();
	CreateResultInput()(input_);
	FuncData funcData{ 
		.changeGame{std::bind_front(&ResultScene::ChangeGame, this)},
		.changeSelect{std::bind_front(&ResultScene::ChangeSelect, this)}
	};
	core_ = std::make_unique<GameCore>(SetUpResultScene(filePass,result, funcData));

	auto scoreDatas = HistoryScoreLoad().Load(filePass);
	scoreDatas.set(static_cast<int>(result->hitsData->score));
	HistoryScoreSave().Save(filePass,scoreDatas);

	DrawOnScreen();
}

ResultScene::~ResultScene()
{
}

void ResultScene::ProcessInput()
{
	BaseScene::ProcessInput();
	core_->ProcessInput();
}

std::unique_ptr<BaseScene> ResultScene::Update(std::unique_ptr<BaseScene> inScene)
{
	core_->Update(timer_->GetDeletaTime(),*input_);
	DrawOnScreen();
	return (nextScene_.operator bool() == true ? std::move(nextScene_) : std::move(inScene));;
}

void ResultScene::DrawOnScreen()
{
	SetDrawScreen(handle_);
	ClearDrawScreen();
	core_->Draw();
}

void ResultScene::ChangeGame(std::string pass)
{
	nextScene_ = std::make_unique<GameScene>(sortIndex_,groupIndex_,type_,pass);
}

void ResultScene::ChangeSelect(void)
{
	nextScene_ = std::make_unique<SelectScene>(sortIndex_, groupIndex_, type_);
}
