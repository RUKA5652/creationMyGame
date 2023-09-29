#pragma once
#include"../../../Base/BaseData.h"
#include"../../../template/Vector2.h"

struct LaneBox 
	:public BaseData
{
	using Pos = Vector2Tmple<int>;
	LaneBox(Pos LT, Pos RB);

	const Pos LT;
	const Pos RB;

};

