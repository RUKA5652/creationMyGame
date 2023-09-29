#include "LaneDivision.h"
#include"../../../WindowSize.h"
#include"LaneLength.h"



LaneDivision::LaneDivision(const Beat::DifficultyPtr& data, const SideSpaceDivision* sideData,
	LaneLengthConstPtr&& lengthData) : divisionData(data->CircleSize)
{
	CreateDivisionBox(*sideData,lengthData);
}

LaneDivision::LaneDivision(int div, const SideSpaceDivision* sideData,
	LaneLengthConstPtr lengthData)
	:divisionData(div)
{
	CreateDivisionBox(*sideData, lengthData);
}

const std::vector<LaneBox>& LaneDivision::GetBoxVec() const
{
	return boxVec_;
}

const LaneDivision::BothEnds LaneDivision::GetBothEnds() const
{
	return { boxVec_.begin()->LT.x, (--boxVec_.end())->RB.x };
}

const LaneDivision::BoxSize& LaneDivision::GetBoxSize() const
{
	return size_;
}

void LaneDivision::CreateDivisionBox(const SideSpaceDivision& sideData, LaneLengthConstPtr& lengthData)
{
	auto spaceRatio = sideData.GetDivisionSpaceRatio();
	auto& windowSize = lpWindowSize->GetSize();

	auto divisionSpace = static_cast<int>(windowSize.x * spaceRatio);

	auto laneDiveSize = static_cast<int>( (windowSize.x - (divisionSpace * 2)) * (1.0 / divisionData) );

	auto endPos = windowSize.x - divisionSpace;

	auto length = lengthData->GetLength();

	for (int i = 0, x2 = 0; i < divisionData; i++)
	{
		auto x1 = (divisionSpace + laneDiveSize * i);
		x2 = (x1 + laneDiveSize);
		boxVec_.emplace_back(LaneBox::Pos{ x1,0 }, LaneBox::Pos{ x2,length });

	}
}



