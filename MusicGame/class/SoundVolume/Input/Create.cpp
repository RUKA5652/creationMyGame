#include "Create.h"
#include"../../Input/EnumCast.h"
#include"Enum.h"
#include<DxLib.h>

using namespace keytype;

void CreateVoulumeInput::operator()(InputManagerPtr& ptr)
{
	if (!ptr)
	{
		ptr = std::make_unique<InputManager>(
			std::vector<std::pair<int, int>>{ {
				{Cast(VolumeInput::SeUp),KEY_INPUT_NUMPAD7},
				{Cast(VolumeInput::SeDown),KEY_INPUT_NUMPAD4},
				{Cast(VolumeInput::SongUp),KEY_INPUT_NUMPAD8},
				{Cast(VolumeInput::SongDown),KEY_INPUT_NUMPAD5},
			} }
		);
	}
}