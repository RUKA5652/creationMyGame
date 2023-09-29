#pragma once
#include "BaseScene.h"
#include"../Common/osu/Result/ResultData.h"
#include"../Common/osu/Select/Reel/ReelData.h"
#include<string>
#include<functional>


class GameScene :
    public BaseScene
{
public:
	using ChengeFuncResult = std::function<void(Beat::ResultDataConstPtr)>;

	GameScene(int sortIndex,int groupIndex,Beat::ReelSortType type,std::string filePass);
	~GameScene();
	void ProcessInput() override;

	//gameシュミュレーション
	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> inScene) override;


private:
	void Init();

	void ChengeResult(Beat::ResultDataConstPtr result);

	void ChengeSelect();

	std::unique_ptr<BaseScene> nextScene_;

	std::string filePass_;

	int sortIndex_; 
	int groupIndex_; 
	int soundHandle_;
	Beat::ReelSortType type_;
};

