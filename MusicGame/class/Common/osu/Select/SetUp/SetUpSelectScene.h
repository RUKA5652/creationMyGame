#pragma once
#include "../../../Base/SetUp/SetUpGameObj.h"
#include"../Reel/Reel.h"
#include"../../../../Scene/UsingChangeSceneFunc.h"

class ReelSound;

class SetUpSelectScene :
    public SetUpGameObj
{
public:
	SetUpSelectScene(ChengeSceneFunc::CreateGameFunc func);
	SetUpSelectScene(Beat::ReelDataPtr& reelData, ReelSound*& reelSound,ChengeSceneFunc::CreateGameFunc func);
private:
	const ChengeSceneFunc::CreateGameFunc func_;
	Beat::ReelDataPtr reelData_;
	ReelSound* reelSound_;
	void MakeObj() override;

};

