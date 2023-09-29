#pragma once
#include"../LoadSectionBase.h"
#include"../../../TimingPointsData.h"

class TimingPointsLoad:
	public LoadSectionBase<TimingPoints>
{
public:
	TimingPointsLoad();

	bool LoadFile(const std::string& fileData, Beat::LoadDataPtr data) override;
private:

	void Init();

};

