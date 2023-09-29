#include "SetUpSelectScene.h"
#include"../Reel/Reel.h"
#include"../Reel/ReelData.h"
#include"../Reel/Sound/ReelSound.h"
#include"../UI/SelectUI.h"


SetUpSelectScene::SetUpSelectScene(ChengeSceneFunc::CreateGameFunc func)
	:func_(func)
{
	reelData_ = std::make_shared<Beat::ReelData>();
	reelSound_ = nullptr;
}

SetUpSelectScene::SetUpSelectScene(Beat::ReelDataPtr& reelData, ReelSound*& reelSound, ChengeSceneFunc::CreateGameFunc func)
	: func_(func)
{
	if (!reelData)
	{
		reelData = std::make_shared<Beat::ReelData>();
	}
	if (!reelSound)
	{
		reelSound = new ReelSound(reelData);
	}
	reelData_ = reelData;
	reelSound_ = reelSound;
}

void SetUpSelectScene::MakeObj()
{
	SetGameObj(std::make_unique<Reel>(reelData_, reelSound_, func_));
	SetGameObj(std::make_unique<SelectUI>());
}
