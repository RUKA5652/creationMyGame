#pragma once
#include"../BaseCreateInput.h"
#include"SpeedAdjustInput.h"

class CreateSpeedAdjustInput:
	public BaseCreateInput
{
public:
	void operator()(InputManagerPtr& ptr) override;



private:



};

