#pragma once
#include"../ReelData.h"
#include<fstream>

class SaveReelData
{
public:
	SaveReelData();
	~SaveReelData();
	void operator()(Beat::ReelData* reelData);

private:
	void SaveData();



	Beat::ReelData* reelData_;

};

