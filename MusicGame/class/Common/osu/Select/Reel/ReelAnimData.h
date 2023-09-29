#pragma once

struct ReelAnimData
{
	enum class State
	{
		SeletNow,
		SeletEndAnim,
	};

	State state;
};

