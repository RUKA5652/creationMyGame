#include "SelectScene.h"
#include"../Manager/SceneManager.h"
#include"../Common/osu/Select/SetUp/SetUpSelectScene.h"
#include"GameScene.h"
#include "../../_debug/_DebugConOut.h"
#include"../Input/Select/CreateSelectInput.h"
#include "TestScene.h"
#include"ResultScene.h"
#include"../Common/osu/Select/Reel/Sound/ReelSound.h"
#include"ChangeEffect/ChangeEffect.h"
#include"TitleScene.h"
#include"../Common/osu/Select/Reel/Data/SortReelData.h"
#include "../Input/EnumCast.h"
#include"SpeedAdjustmentScene.h"
#include "../SoundVolume/SoundVolume.h"

SelectScene::SelectScene()
{
	reelData_ = nullptr;
	reelSound_ = nullptr;
	Init();

}

SelectScene::SelectScene(Beat::ReelDataPtr reelData, ReelSound* reelSound)
{
	reelData_ = reelData;
	reelSound_ = reelSound;
	Init();
}

SelectScene::SelectScene(int sortIndex, int groupIndex, Beat::ReelSortType type)
{
	reelData_ = nullptr;
	reelSound_ = nullptr;
	Init();
	if (reelData_->sortType.value() != type)
	{
		SortReelData sort(reelData_);
		sort.CreateSortData();
		sort.Sort(type);
	}
	reelData_->mainSortIndex_ = sortIndex;
	reelData_->mapGroupIndex_ = groupIndex;
}

SelectScene::~SelectScene()
{
	TRACE("セレクト破棄");
	DeleteSoundMem(guideHandle_);
	delete titleBackEffect_;
	if (soundDeletFlag_)
	{
		delete reelSound_;
	}

}

void SelectScene::ProcessInput()
{
	BaseScene::ProcessInput();
	core_->ProcessInput();
	if (nextScene_)
	{
		nextScene_->TimeUpdate();
	}

	if (!guidFlag_)
	{
		guidFlag_ = true;
		//PlaySoundMem(guideHandle_, DX_PLAYTYPE_BACK, false);
		lpVolumeMng.PlaySoundMem(guideHandle_, Sound::Type::SE, DX_PLAYTYPE_BACK,false);
	}

}

std::unique_ptr<BaseScene> SelectScene::Update(std::unique_ptr<BaseScene> inScene)
{
	//select_->Update();
	if (!titleBackEffect_)
	{
		core_->Update(timer_->GetDeletaTime(), *input_);
		if (input_->GetInputData().at(Cast(SELECT::BACK)).oneShot())
		{
			soundDeletFlag_ = false;
			titleBackEffect_ = new ChangeEffect();
			nextScene_ = std::make_unique<TitleScene>(reelData_,reelSound_);
			return inScene;
		}
	}
	else
	{
		nextScene_->DrawUpdate();
		titleBackEffect_->Update(timer_->GetDeletaTime());
		if (titleBackEffect_->GetEnd())
		{
			return std::move(nextScene_);
		}
		else
		{
			return inScene;
		}
	}

	//スピード調整
	if (input_->GetInputData().at(Cast(SELECT::SPEED)).oneShot())
	{
		return std::make_unique<SpeedAdjustmentScene>( std::move(inScene));
	}

	return (nextScene_.operator bool() == true ? std::move(nextScene_) : std::move(inScene));
}

void SelectScene::DrawOnScreen()
{
	SetDrawScreen(handle_);
	ClearDrawScreen();
	core_->Draw();
	if (titleBackEffect_)
	{
		titleBackEffect_->Draw(this, nextScene_.get());
	}
}


void SelectScene::ChengeGame(const std::string& path)
{
	soundDeletFlag_ = true;
	nextScene_ = std::make_unique<GameScene>(reelData_->mainSortIndex_.value(), reelData_->mapGroupIndex_.value(), reelData_->sortType.value(), path);
}

void SelectScene::Init()
{
	soundDeletFlag_ = false;
	titleBackEffect_ = nullptr;
	guideHandle_ = LoadSoundMem("resource/skin/Select/guide.wav");
	CreateSelectInput()(input_);
	timer_ = std::make_unique<LoopTimer>();
	if (!core_)
	{
		core_ = std::make_unique<GameCore>(SetUpSelectScene(reelData_, reelSound_, std::bind_front(&SelectScene::ChengeGame, this)));
	}
}

