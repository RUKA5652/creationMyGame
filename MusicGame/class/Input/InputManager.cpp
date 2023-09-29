#include "InputManager.h"
#include <DxLib.h>


InputManager::InputManager(std::vector<std::pair<KeyCode, int>>&& init)
{
	for (auto& data : init)
	{
		inputData_.try_emplace(data.first, InputData{data.second});
	}
	Update(0);

}

InputManager::~InputManager()
{
}

void InputManager::Update(Timer::DeletaTimeConst& deletTime)
{

	GetHitKeyStateAll(data.data());
	for (auto& [key, result] : inputData_)
	{
		result.old = result.now;
		result.now = data[result.key];
		result.pushTime = result.now ? result.pushTime + deletTime : 0;
	}

}

const InputManager::InputResult& InputManager::GetInputData() const
{
	return inputData_;
}

InputManager::InputData::InputData(KeyCode key)
{
	this->key = key;
	now = false;
	old = true;
	pushTime = 0;
}

InputManager::InputData::InputData()
{
	key = -1;
	now = false;
	old = true;
	pushTime = 0;
}
