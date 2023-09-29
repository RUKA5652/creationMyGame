#pragma once
#include"../../Base/BaseData.h"
#include<memory>
#include "HitObj/NoteData.h"
#include"NoteSizeRatio.h"
#include"Lane/LaneLength.h"


class DecisionTransform
	:public BaseData
{
public:

	DecisionTransform(NoteSizeRatioConstPtr noteSize, LaneLengthConstPtr length);

	const Note::Size& GetSize() const;

	const int GetOffset() const;

private:

	NoteSizeRatioConstPtr noteSize_;

	int offset_;

	void CreateOffset(LaneLengthConstPtr& length);
};

using DecisionTransformPtr = std::shared_ptr<DecisionTransform>;
using DecisionTransformConstPtr = std::shared_ptr<const DecisionTransform>;