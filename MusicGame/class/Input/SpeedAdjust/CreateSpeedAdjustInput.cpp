#include "CreateSpeedAdjustInput.h"
#include"../EnumCast.h"
#include<DxLib.h>

using namespace keytype;

void CreateSpeedAdjustInput::operator()(InputManagerPtr& ptr)
{


	if (!ptr)
	{
		ptr = std::make_unique<InputManager>(
			std::vector<std::pair<int, int>>{ {
				{Cast(SPEEDADJUST::UP),KEY_INPUT_UP},
				{Cast(SPEEDADJUST::DOWN),KEY_INPUT_DOWN},
				{Cast(SPEEDADJUST::LEFT),KEY_INPUT_LEFT},
				{Cast(SPEEDADJUST::RIGHT),KEY_INPUT_RIGHT},
				{Cast(SPEEDADJUST::BACK), KEY_INPUT_ESCAPE },
			} }
		);
	}
}