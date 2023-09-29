#include "CreateResultInput.h"
#include"../EnumCast.h"
#include<DxLib.h>

using namespace keytype;

void CreateResultInput::operator()(InputManagerPtr& ptr)
{

	if (!ptr)
	{
		ptr = std::make_unique<InputManager>(
			std::vector<std::pair<int,int>>{
				{Cast(RESULT::LEFT),KEY_INPUT_LEFT},
				{Cast(RESULT::RIGHT),KEY_INPUT_RIGHT},
				{ Cast(RESULT::UP),KEY_INPUT_UP },
				{ Cast(RESULT::DOWN),KEY_INPUT_DOWN },
				{Cast(RESULT::DECIDE),KEY_INPUT_RETURN },
				{Cast(RESULT::BACK),KEY_INPUT_ESCAPE},
			}
		);
	}
}
