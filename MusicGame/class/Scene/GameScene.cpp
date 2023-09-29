#include "GameScene.h"
#include<DxLib.h>
#include"../Common/osu/game/SetUp/SetUpGameScene.h"
#include"../Manager/SceneManager.h"
#include"SelectScene.h"
#include"ResultScene.h"
#include"../Input/Game/GameSceneInputKey.h"
#include "../Input/EnumCast.h"

GameScene::GameScene(int sortIndex, int groupIndex, Beat::ReelSortType type,std::string filePass)
    :filePass_(filePass)
{
    sortIndex_ = sortIndex;
    groupIndex_ = groupIndex;
    type_ = type;
    core_ = std::make_unique<GameCore>(SetUpGameScene(filePass_,input_,timer_, soundHandle_, std::bind_front(&GameScene::ChengeResult, this)));
    Init();
    DrawOnScreen();
    timer_->Reset();
}

GameScene::~GameScene()
{
   
}

void GameScene::ProcessInput()
{
    BaseScene::ProcessInput();
    core_->ProcessInput();
    if (nextScene_)
    {
        nextScene_->TimeUpdate();
    }
}

std::unique_ptr<BaseScene> GameScene::Update(std::unique_ptr<BaseScene> inScene)
{
    core_->Update(timer_->GetDeletaTime(), *input_);
    if (input_->GetInputData().at(Cast(GAME::PAUSE)).oneShot())
    {
        inScene = std::make_unique<SelectScene>(sortIndex_, groupIndex_, type_);
        return inScene;
    }
    return ((nextScene_  && timer_->GetDeletaTime() == 0 )? std::move(nextScene_) : std::move(inScene));
}




void GameScene::Init()
{
   // timer_ = std::make_unique<LoopTimer>();
}

void GameScene::ChengeResult(Beat::ResultDataConstPtr result)
{
    if (nextScene_ || timer_->GetDeletaTime() != 0)
    {
        return;
    }
    nextScene_ = std::make_unique<ResultScene>(sortIndex_,groupIndex_,type_,filePass_,result);
}

void GameScene::ChengeSelect()
{
    if (nextScene_)
    {
        return;
    }
    nextScene_ = std::make_unique<SelectScene>(sortIndex_, groupIndex_, type_);
}
