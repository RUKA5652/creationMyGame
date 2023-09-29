#pragma once
#include"../ReelData.h"
#include<map>
#include"ReelSoundLoad.h"

class ReelSound
{
public:
	using SoundsData = std::map<std::string, int>;


	ReelSound(Beat::ReelDataPtr reelData);

	~ReelSound();

	std::optional<std::pair<std::string, int*>> Update(bool flag);

	std::pair<std::string, int*> LoadSound();
	std::pair<std::string, int*> LoadNowSound();

	void SetRandomSound();

private:
	Beat::ReelDataPtr reelData_;
	//using SoundsData = std::pair<std::string, int>;
	SoundsData soundData_;
	SoundsData::iterator nowSound_;

	ReelSoundLoad load_;

	friend ReelSoundLoad;
};

