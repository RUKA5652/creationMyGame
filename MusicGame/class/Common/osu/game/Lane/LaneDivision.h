#pragma once
#include"../../../Base/BaseData.h"
#include<memory>
#include<vector>
#include"../../Difficulty.h"
#include"../SideSpaceDivision.h"
#include"LaneBox.h"
#include"LaneLength.h"


/// <summary>
/// ���[���̕������
/// </summary>
class LaneDivision
	:public BaseData
{
public:
	struct BothEnds
	{
		int front;
		int back;
	};

	struct BoxSize
	{
		int Hyde;
		int Wide;
	};

	LaneDivision(const Beat::DifficultyPtr& data, 
		const SideSpaceDivision* sideData, 
		LaneLengthConstPtr&& lengthData);

	LaneDivision(int div, const SideSpaceDivision* sideData,
		LaneLengthConstPtr lengthData);

	/// <summary>
	/// ������ ���[����
	/// </summary>
	const int divisionData;

	const std::vector<LaneBox>& GetBoxVec()const;
	/// <summary>
	/// ���[���S�̂̉����W
	/// </summary>
	/// <returns>�����W�A�E���W</returns>
	const BothEnds GetBothEnds() const;

	const BoxSize& GetBoxSize()const;

private:
	
	std::vector<LaneBox> boxVec_;

	BoxSize size_;

	void CreateDivisionBox(const SideSpaceDivision& sideData, LaneLengthConstPtr& lengthData);

};

using LaneDivisionPtr = std::shared_ptr<LaneDivision>;
using LaneDivisionConstPtr = std::shared_ptr<const LaneDivision>;