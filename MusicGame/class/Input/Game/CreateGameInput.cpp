#include "CreateGameInput.h"
#include"../EnumCast.h"
#include<DxLib.h>
#include"../../Common/osu/game/Key/KeyData.h"

using namespace keytype;

void CreateGameInput::operator()(InputManagerPtr& ptr)
{

	if (!ptr)
	{
		ptr = std::make_unique<InputManager>(
			std::vector<std::pair<InputManager::KeyCode,int>>{
				{Cast(GAME::LANE1),KEY_INPUT_D},
				{Cast(GAME::LANE2),KEY_INPUT_F},
				{Cast(GAME::LANE3),KEY_INPUT_J},
				{Cast(GAME::LANE4),KEY_INPUT_K},
				{Cast(GAME::PAUSE),KEY_INPUT_ESCAPE},
			}
		);
	}
}

void CreateGameInput::operator()(InputManagerPtr& ptr, int size)
{
	auto data = KeyData()(size);
	std::vector<std::pair<int, int>> inputData;
	for (int i = 0; i < data.size(); i++)
	{
		inputData.emplace_back(i + Cast(GAME::LANE1), data[i].second);
	}
	inputData.emplace_back(Cast(GAME::PAUSE), KEY_INPUT_ESCAPE);
	ptr = std::make_unique<InputManager>(std::move(inputData));

}
