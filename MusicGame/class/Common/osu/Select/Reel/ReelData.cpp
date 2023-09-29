#include"ReelData.h"

using namespace Beat;

const ReelData::MapGroup* Beat::ReelData::GetMapGroupData() const
{
	if (!mainSortIndex_)
	{
		return nullptr;
	}
	return &sortData[mainSortIndex_.value()];
}

const BeatMap* Beat::ReelData::GetMapData() const
{
	if (!mapGroupIndex_ || !mainSortIndex_)
	{
		return nullptr;
	}
	return sortData[mainSortIndex_.value()][mapGroupIndex_.value()];
}

bool Beat::ReelData::MoveMainSort(int cnt)
{
	if (!mainSortIndex_)
	{
		return false;
	}
	bool flag = false;
	auto index = mainSortIndex_.value();
	index += cnt;
	if (index < 0 || index >= sortData.size())
	{
		index = std::clamp(index, 0,static_cast<int>(sortData.size()) - 1);
		flag = true;
	}
	mainSortIndex_ = index;
	if (!flag)
	{
		mapGroupIndex_ = cnt > 0 ? 0 : static_cast<int>(sortData[index].size()) - 1;
	}


	return flag;
}

bool Beat::ReelData::MoveBeatMap(int cnt)
{
	if (!mainSortIndex_ || !mapGroupIndex_)
	{
		return false;
	}
	bool flag = false;
	auto& groupData = sortData[mainSortIndex_.value()];
	auto index = mapGroupIndex_.value();
	index += cnt;
	if (index < 0 || index >= groupData.size())
	{
		index = std::clamp(index, 0, static_cast<int>(groupData.size()) - 1);
		flag = true;
	}
	mapGroupIndex_ = index;

	return flag;
}
