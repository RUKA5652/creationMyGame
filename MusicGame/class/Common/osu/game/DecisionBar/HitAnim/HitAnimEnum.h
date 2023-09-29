#pragma once
#include<functional>
#include"../../HitObj/NoteData.h"

namespace Decision
{
	enum class AnimType
	{
		Normal,
		Holde,
		MAX,
	};

	using AnimSetFunc = std::function<void(int,bool, AnimType)>;

}

