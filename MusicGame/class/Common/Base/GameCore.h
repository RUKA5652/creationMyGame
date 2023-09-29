#pragma once
#include<memory>
#include<map>
#include<functional>
#include<vector>
#include"Update/UpdateBase.h"
#include"Draw/DrawBase.h"
#include"GameObjBase.h"
#include "BaseData.h"
#include"Update/UpdateBase.h"
#include "../../Timer/Timer.h"
#include<mutex>

//
class GameClock;
class SideSpaceDivision;


namespace Beat
{
	struct DrawMode;
	struct Difficulty;
};


/// <summary>
/// GameObjからセットされたデータを更新する
/// </summary>
class GameCore
{
public:
	

	GameCore(SetUpGameObj& setUp);
	GameCore(SetUpGameObj&& setUp);
	~GameCore();

	void ProcessInput();

	void Update(Timer::DeletaTimeConst& delta, const InputManager& input);
	void DrawUpdate(Timer::DeletaTimeConst& delta, const InputManager& input);
	void Draw();

	void SetDraw(int priority, const DrawBasePtr& draw);


private:
	std::vector<ObjBasePtr> objData_;

	std::multimap<int, DrawBasePtr> draw_;

	std::mutex mtx_;
	friend SetUpGameObj;
};

