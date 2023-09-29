#pragma once
#include<cmath>
#include<algorithm>

inline namespace animCurve
{
	//
	inline float BaseCurve(float time, float sharp)
	{
		float x = std::exp(-std::clamp(time, 0.0f, 1.0f) * sharp);
		float s0 = 1;
		float s1 = std::exp(-sharp);
		return (x - s0) / (s1 - s0);
	}
	//
	inline float ReBaseCurve(float time, float sharp)
	{
		time = std::clamp(time, 0.0f, 1.0f);
		return 1 - BaseCurve(1 - time, sharp);
	}

	inline float MoveOutIn(float time, float sharp)
	{
		time = std::clamp(time, 0.0f, 1.0f);
		time = 1 - time;
		return 1 - time * time * (sharp * time - sharp + 1);
	}
};

