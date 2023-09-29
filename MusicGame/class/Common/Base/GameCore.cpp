#include "GameCore.h"
#include"SetUp/SetUpGameObj.h"
#include"../WindowSize.h"
#include <cassert>
#include<DxLib.h>
#include <algorithm>
#include <execution>
#include "../../Input/InputManager.h"


GameCore::GameCore(SetUpGameObj& setUp)
{
	setUp.SetUp(this);
}

GameCore::GameCore(SetUpGameObj&& setUp)
	:GameCore(setUp)
{

}

GameCore::~GameCore()
{
	for (auto& obj : objData_)
	{
		obj.reset();
	}
}


void GameCore::ProcessInput()
{
}

void GameCore::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	std::for_each(objData_.begin(), objData_.end(), [&](ObjBasePtr& update) {update->Update(delta,input); });
	std::for_each(std::execution::par, draw_.begin(), draw_.end(), [&](auto& draw) {draw.second->Update(delta, input); });
}

void GameCore::DrawUpdate(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	std::for_each(std::execution::par, draw_.begin(), draw_.end(), [&](auto& draw) {draw.second->Update(delta, input); });
}

void GameCore::Draw()
{
	for (auto& obj : draw_)
	{
		obj.second->Draw();
	}
}

void GameCore::SetDraw(int priority, const DrawBasePtr& draw)
{
	std::lock_guard<std::mutex> lock(mtx_);

	draw_.emplace(priority, draw);
}

