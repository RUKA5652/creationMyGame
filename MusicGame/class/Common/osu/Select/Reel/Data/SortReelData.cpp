#include "SortReelData.h"
#include<algorithm>

SortReelData::SortReelData(Beat::ReelDataPtr reelData)
{
	reelData_ = std::move(reelData);
	Init();
}

void SortReelData::Sort(Beat::ReelSortType type)
{
	loadFunc_[type]();
	reelData_->sortType = type;
}

void SortReelData::CreateSortData()
{
	sortData_.clear();
	for (auto& data : reelData_->beatMapData)
	{
		sortData_.emplace_back(&data);
	}
}

void SortReelData::Init()
{
	loadFunc_ = {
		{Beat::ReelSortType::Name,std::bind(&SortReelData::NameSort,this)}


	};
}

void SortReelData::NameSort()
{
	if (sortData_.size() == 0)
	{
		return;
	}

	auto& sortData = reelData_->sortData;

	sortData_.sort([](const Beat::BeatMap* in1, const Beat::BeatMap* in2) {return in1->metaDatas.Title < in2->metaDatas.Title; });

	sortData.clear();



	auto itr = sortData_.begin();
	int cnt = 0;
	std::filesystem::path targetFolder = (*itr)->path;
	for (auto& beatMap : sortData_)
	{
		if (targetFolder != beatMap->path)
		{
			auto& resultData = sortData.emplace_back(cnt);
			for (int i = 0; i < resultData.size(); i++)
			{
				resultData[i] = (*itr);
				++itr;
			}
			cnt = 0;
			targetFolder = beatMap->path;
			//continue‚Í—v‚ç‚È‚¢
		}
		cnt++;
	}
	if (targetFolder == (*sortData_.rbegin())->path)
	{
		auto& resultData = sortData.emplace_back(cnt);
		for (int i = 0; i < resultData.size(); i++)
		{
			resultData[i] = (*itr);
			++itr;
		}
	}
	if (!reelData_->sortType || reelData_->sortType.value() != Beat::ReelSortType::Name)
	{
		reelData_->mapGroupIndex_ = 0;
		reelData_->mainSortIndex_ = 0;
	}
}
