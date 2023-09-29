#pragma once
#include"../../../../Base/Draw/DrawBase.h"

class LaneDrawBase :
	public DrawBase
{
public:
	virtual void SetFunc(GameCore* gameCore) override = 0;
};

using LaneDrawBasePtr = std::shared_ptr<LaneDrawBase>;
