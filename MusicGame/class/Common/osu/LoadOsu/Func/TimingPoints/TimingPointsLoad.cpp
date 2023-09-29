#include "TimingPointsLoad.h"
#include"TimingPointsLoadFunc.h"
#include<sstream>

namespace
{
	constexpr auto title("[TimingPoints]");
}


TimingPointsLoad::TimingPointsLoad():
	LoadSectionBase(title)
{
	Init();
}

bool TimingPointsLoad::LoadFile(const std::string& fileData, Beat::LoadDataPtr data)
{
	return LoadSectionBase::LoadFile(fileData, data->timingPoints.get());
}


void TimingPointsLoad::Init()
{
	setDataFuncVec_ =
	{
		TimingPointsLoadFunc::SetData(),
	};
}


