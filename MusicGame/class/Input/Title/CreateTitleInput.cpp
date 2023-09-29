#include "CreateTitleInput.h"
#include"../EnumCast.h"
#include<DxLib.h>

void CreateTitleInput::operator()(InputManagerPtr& ptr)
{


	if (!ptr)
	{
		ptr = std::make_unique<InputManager>(
			std::vector<std::pair<int, int>>{ {
				{Cast(TITLE::UP),KEY_INPUT_UP},
				{Cast(TITLE::DOWN),KEY_INPUT_DOWN},
				{Cast(TITLE::DECIDE),KEY_INPUT_RETURN},
				{ Cast(TITLE::BACK), KEY_INPUT_ESCAPE },
			} }
		);
	}
}