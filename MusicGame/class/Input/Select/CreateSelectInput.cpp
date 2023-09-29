#include "CreateSelectInput.h"
#include"../EnumCast.h"
#include<DxLib.h>

using namespace keytype;

void CreateSelectInput::operator()(InputManagerPtr& ptr)
{


	if (!ptr)
	{
		ptr = std::make_unique<InputManager>(
			std::vector<std::pair<int, int>>{ {
				{Cast(SELECT::UP),KEY_INPUT_UP},
				{Cast(SELECT::DOWN),KEY_INPUT_DOWN},
				{Cast(SELECT::LSKIP),KEY_INPUT_LEFT},
				{Cast(SELECT::RSKIP),KEY_INPUT_RIGHT},
				{Cast(SELECT::DECIDE),KEY_INPUT_RETURN},
				{Cast(SELECT::RELOAD), KEY_INPUT_F5},
				{Cast(SELECT::SPEED), KEY_INPUT_1 },
				{Cast(SELECT::BACK), KEY_INPUT_ESCAPE },
			} }
		);
	}
}