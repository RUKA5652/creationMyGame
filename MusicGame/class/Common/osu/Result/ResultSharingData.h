#pragma once
#include"ResultData.h"
#include"../../../Scene/ResultScene.h"
#include<memory>
#include<vector>

class ResultSharingData
{
public:
	ResultSharingData(const std::string& filePass,Beat::ResultDataConstPtr& resultData, ResultScene::FuncData& func);
	struct Rank
	{
		Rank();
		~Rank();
		void Init(Beat::ResultDataConstPtr& resultDraw);
		void CreateRank(Beat::ResultDataConstPtr& resultDraw);
		Vector2 pos;
		int rankImage;
		int soundHandle;
	};

	struct Select
	{
		Select();
		Vector2 pos;
		float blendParam;
		int image;
		std::function<void(void)> func;
	};


	using SelectsItr = std::vector<std::unique_ptr<Select>>::const_iterator;

	Rank rank;

	std::vector<std::unique_ptr<Select>> selects;

private:
	struct Retry
		:public Select
	{
		Retry(Rank& rank, std::function<void(void)> func );
	};

	struct Back
		:public Select
	{
		Back(std::function<void(void)> func);
	};
};
using ResultSharingDataPtr = std::shared_ptr<ResultSharingData>;
using ResultSharingDataConstPtr = std::shared_ptr<const ResultSharingData>;

