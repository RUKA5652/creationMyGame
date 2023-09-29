#pragma once
#include<memory>
#include "../../../Timer/Timer.h"
#include "../../../Input/InputManager.h"

class GameCore;
class ObjBase;

class DrawBase
	:public std::enable_shared_from_this<DrawBase>
{
public:
	virtual ~DrawBase();

	virtual void Update(Timer::DeletaTimeConst& delta, const InputManager& input);
	virtual void Draw() = 0;

private:
	virtual void SetFunc(GameCore* gameCore) = 0;

	friend ObjBase;
};

using DrawBasePtr = std::shared_ptr<DrawBase>;


