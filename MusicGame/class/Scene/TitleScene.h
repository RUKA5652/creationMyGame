#pragma once
#include"BaseScene.h"
#include "../Common/osu/Select/Reel/ReelData.h"
#include<thread>
#include "ChangeEffect/ChangeEffect.h"

class ReelSound;
class TitleScene
	:public BaseScene
{
public:
	TitleScene(Beat::ReelDataPtr reelData, ReelSound* reelSound);
	TitleScene();
	~TitleScene();

	void ProcessInput() override;
	//gameシュミュレーション
	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> inScene) override;

private:
	std::unique_ptr<BaseScene> nextScene_;
	Beat::ReelDataPtr reelData_;
	//std::jthread thread_;

	ReelSound* reelSound_;

	bool changeFlag_;

	ChangeEffect changeEffect_;

	void Init();
	void ChengeSelect();
	void DrawOnScreen() override;


};

