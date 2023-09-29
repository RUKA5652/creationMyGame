#pragma once
#include<optional>
#include"../ReelData.h"
#include "../../../LoadOsu/LoadOsuFile.h"
#include"Load/LoadFolder.h"

class LoadReelData
{
public:
	LoadReelData();
	void operator()(Beat::ReelData* reelData);
private:
	Beat::ReelData* reelData_;

	//�������^�C�~���O��x�点����
	std::unique_ptr<LoadOsuFile> loadClass_;

	Beat::LoadDataPtr oneLoadData_;

	LoadFolder load_;

	bool CheckMusicList();

	bool CheckBeatMapCount();

	void LoadListData();


};

