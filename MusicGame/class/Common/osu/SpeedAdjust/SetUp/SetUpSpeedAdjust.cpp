#include "SetUpSpeedAdjust.h"
#include"../SpeedAdjust.h"

SetUpSpeedAdjust::SetUpSpeedAdjust()
{
}

void SetUpSpeedAdjust::MakeObj()
{
	SetGameObj(std::make_unique<SpeedAdjust>());
}
