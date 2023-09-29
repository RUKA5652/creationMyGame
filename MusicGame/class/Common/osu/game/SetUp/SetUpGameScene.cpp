#include "SetUpGameScene.h"
#include<filesystem>
#include"../../LoadOsu/LoadOsuFile.h"
#include"../Lane/CreateLane.h"
#include"../HitObj/CreateNotes.h"
#include"../Combo/Combo.h"
#include"../Score/Score.h"
#include"../BackImage/BackImage.h"
#include"../../../../Input/Game/CreateGameInput.h"
#include"../../../../Timer/Game/GameClock.h"
#include "../DecisionBar/DecisionBar.h"
#include"../UI/GameUI.h"



SetUpGameScene::SetUpGameScene(const std::string& musicScorePass, InputManagerPtr& input, LoopTimerPtr& timer,
	int& soundHande,GameScene::ChengeFuncResult func)
	: func_(func)
{
	Init(musicScorePass, input,timer,soundHande);
}


void SetUpGameScene::Init(const std::string& musicScorePass, InputManagerPtr& input, 
	LoopTimerPtr& timer, int& soundHande)
{
	LoadFile(musicScorePass, input,timer,soundHande);
}

void SetUpGameScene::LoadFile(const std::string& musicScorePass, InputManagerPtr& input, LoopTimerPtr& timer, int& soundHande)
{
	LoadOsuFile fileLoader;
	fileLoader.LoadFile(musicScorePass);
	loadData_ = fileLoader.GetLoadData();
	std::filesystem::path path(musicScorePass);
	path.replace_filename(loadData_->generalData->AudioFilename);
	CreateGameInput()(input, loadData_->difficulty->CircleSize);
	timer = std::make_unique<GameClock>(path.string(),loadData_,soundHande);
	SetGameObj(std::make_unique<BackImage>(musicScorePass, loadData_->eventsData->image_));
}



void SetUpGameScene::MakeObj()
{


	auto sideSpaceData = new SideSpaceDivision();
	CreateLane creatLane(loadData_, sideSpaceData);
	auto laneInit = creatLane.CreateInitData();

	CreateNotes createNotes(loadData_->hitObjVec,
		laneInit->division, laneInit->length);
	auto notesInit = createNotes.CreateInitData();

	auto resultData = std::make_shared<Beat::ResultData>(loadData_->eventsData->image_, notesInit->hitdata);
	std::function<void(void)> func = std::bind(func_, resultData);
	auto combo = std::make_unique<Combo>(notesInit->hitdata);

	SetGameObj(creatLane.CreateObj());
	SetGameObj(std::make_unique<DecisionBar>(notesInit->hitdata,
		notesInit->decisionData, laneInit->division, notesInit->noteSize, notesInit->noteData,loadData_));
	SetGameObj(std::move(combo));
	SetGameObj(std::make_unique<Score>(notesInit->hitdata));
	SetGameObj(createNotes.CreateObj(func));
	SetGameObj(std::make_unique<GameUI>(laneInit->division, notesInit->decisionData));

}



