#pragma once
#include"../LoadSectionBase.h"

class CreateScoreMag
	:public Beat::LoadModule
{
public:
	CreateScoreMag();

	bool LoadFile(const std::string& fileData, Beat::LoadDataPtr data) override;

	Beat::Time CreateMidpoint(TimingPointsPtr& timingPoint);

	int MaxConboCount(HitObjVecPtr& data, Beat::Time midpoint);

	void CreateMagData(Beat::ScoreMagData& magData);

	void CreateLevel(Beat::ScoreMagData& magData);

private:
	std::vector<int> scoreLevel_;

};

