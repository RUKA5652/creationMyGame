#pragma once
#include"../ReelData.h"
#include"ReelSortType.h"
#include<map>
#include<functional>

class SortReelData
{
public:
	SortReelData(Beat::ReelDataPtr reelData);

	void Sort(Beat::ReelSortType type);

	void CreateSortData();
private:

	Beat::ReelDataPtr reelData_;

	std::list<const Beat::BeatMap*> sortData_;

	std::map<Beat::ReelSortType, std::function<void(void)>> loadFunc_;

	void Init();

	void NameSort();


};

