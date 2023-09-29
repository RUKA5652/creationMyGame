#pragma once
#include "../../LoadConfigData.h"


struct GetPriorTime
{
	const double  msClock = 0.016 ;
	double operator()(int length)
	{
		return (length / static_cast<double>(lpConfigData->GetConfigData().ManiaSpeed)) * msClock * 1000;
	}
	double operator()(int length,int speed)
	{
		return (length / static_cast<double>(speed)) * msClock * 1000;
	}
};
