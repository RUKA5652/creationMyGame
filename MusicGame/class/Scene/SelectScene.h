#pragma once
#include "BaseScene.h"
#include"../Common/osu/Select/Reel/ReelData.h"

class ReelSound;
class ChangeEffect;

class SelectScene :
    public BaseScene
{
public:
	

	SelectScene();
	SelectScene(Beat::ReelDataPtr reelData, ReelSound* reelSound);
	SelectScene(int sortIndex, int groupIndex, Beat::ReelSortType type);
	~SelectScene();
	void ProcessInput() override;
	//gameシュミュレーション
	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> inScene) override;

	void DrawOnScreen() override;
private:
	std::unique_ptr<BaseScene> nextScene_;
	ChangeEffect* titleBackEffect_;

	Beat::ReelDataPtr reelData_;
	ReelSound* reelSound_;

	int guideHandle_;
	bool guidFlag_;

	bool soundDeletFlag_;

	void ChengeGame(const std::string& path);


	void Init();

	

};

