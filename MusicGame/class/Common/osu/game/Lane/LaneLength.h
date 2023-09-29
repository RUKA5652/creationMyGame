#pragma once
#include"../../../Base/BaseData.h"

/// <summary>
/// ���[���̒���������
/// </summary>
class LaneLength
	:public BaseData
{
public:
	using Length = int;


	LaneLength();

	const Length& GetLength() const;

private:

	Length length_;


};

using LaneLengthPtr = std::shared_ptr<LaneLength>;
using LaneLengthConstPtr = std::shared_ptr<const LaneLength>;
