#pragma once
#include"InputManager.h"

inline namespace keytype
{

	inline InputManager::KeyCode Cast(auto&& inEnum)
	{
		return static_cast<InputManager::KeyCode>(inEnum);
	}


}
