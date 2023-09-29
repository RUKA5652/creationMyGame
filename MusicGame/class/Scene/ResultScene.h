#pragma once
#include"BaseScene.h"
#include"../Common/osu/Result/ResultData.h"
#include"../Common/osu/Select/Reel/Data/ReelSortType.h"
#include<functional>


class ResultScene
	:public BaseScene
{
public:
	using ChangeGameFunc = std::function<void(std::string)>;
	using ChangeSelectFunc = std::function<void(void)>;

	struct FuncData
	{
		ChangeGameFunc changeGame;
		ChangeSelectFunc changeSelect;
	};

	ResultScene(int sortIndex, int groupIndex, Beat::ReelSortType type,const std::string& filePass , Beat::ResultDataConstPtr result);
	~ResultScene();

	void ProcessInput() override;

	//gameシュミュレーション
	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> inScene) override;

	void DrawOnScreen() override;


private:

	void ChangeGame(std::string pass);
	void ChangeSelect(void);

	std::unique_ptr<BaseScene> nextScene_;

	int sortIndex_;
	int groupIndex_;
	Beat::ReelSortType type_;
};

