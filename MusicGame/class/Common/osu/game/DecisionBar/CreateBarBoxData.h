#pragma once
#include"../DecisionTransform.h"
#include"../Lane/LaneDivision.h"

struct CreateBarBoxData
{
	std::vector<LaneBox> operator()(LaneDivisionConstPtr& division, DecisionTransformConstPtr& transform)
	{
		std::vector<LaneBox> boxVec;
		for (auto& box : division->GetBoxVec())
		{
			boxVec.emplace_back(
				LaneBox::Pos{ box.LT.x, transform->GetOffset() },
				LaneBox::Pos{ box.RB.x, transform->GetOffset() + transform->GetSize().y });
		};
		boxVec.shrink_to_fit();
		return boxVec;
	}
};

