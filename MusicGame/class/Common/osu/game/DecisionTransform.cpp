#include "DecisionTransform.h"
#include"NoteSizeRatio.h"
#include"Lane/LaneLength.h"



DecisionTransform::DecisionTransform(NoteSizeRatioConstPtr noteSize, LaneLengthConstPtr length)
{
	noteSize_ = noteSize;
	CreateOffset(length);
}

const Note::Size& DecisionTransform::GetSize() const
{
	return noteSize_->GetSize();
}

const int DecisionTransform::GetOffset() const
{
	return offset_;
}

void DecisionTransform::CreateOffset(LaneLengthConstPtr& length)
{
	offset_ = length->GetLength() - noteSize_->GetSize().y * 2 - 100;
}
