#pragma once
#include "../../../Base/SetUp/SetUpGameObj.h"
#include<string>
#include"../../../../Scene/GameScene.h"
#include"../../LoadData.h"
#include"../../../../Input/InputManager.h"
#include"../../../../Timer/LoopTimer.h"

class SetUpGameScene :
    public SetUpGameObj
{
public:
	SetUpGameScene(const std::string& musicScorePass, InputManagerPtr& input, LoopTimerPtr& timer,int& soundHande, GameScene::ChengeFuncResult func);

private:

	void Init(const std::string& musicScorePass, InputManagerPtr& input, LoopTimerPtr& timer, int& soundHande);

	void LoadFile(const std::string& musicScorePass, InputManagerPtr& input, LoopTimerPtr& timer, int& soundHande);

	void MakeObj() override;

	Beat::LoadDataCPtr loadData_;

	GameScene::ChengeFuncResult func_;

};

