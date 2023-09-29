#include "NoteSizeRatio.h"
#include"Lane/LaneDivision.h"


NoteSizeRatio::NoteSizeRatio(LaneDivisionConstPtr&& division)
{
	LoadRatio(division);
}

const double& NoteSizeRatio::GetHeightRatio() const
{
	return ratio_;
}

const Note::Size& NoteSizeRatio::GetSize() const
{
	return size_;
}

void NoteSizeRatio::LoadRatio(LaneDivisionConstPtr& division)
{
	ratio_ = 1.0 / 18.0;
	ratio_ = 1.0 / 36.0;
	auto& box = division->GetBoxVec()[0];
	size_.x = box.RB.x - box.LT.x;
	size_.y = static_cast<int>(box.RB.y * ratio_);
}
