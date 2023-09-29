#include "GameObjBase.h"
#include<algorithm>
#include <execution>
#include "../../../_debug/_DebugConOut.h"

ObjBase::ObjBase(size_t updateNum, size_t drawNum)
{
	update_.reserve(updateNum);
	draw_.reserve(drawNum);
}

ObjBase::~ObjBase()
{
	TRACE("OBJ‰ð•ú\n");
}

void ObjBase::Update(Timer::DeletaTimeConst& delta,const InputManager& input)
{
	std::for_each(update_.begin(), update_.end(), [&](auto& update) {update->Update(delta, input); });
}

void ObjBase::SetDraw(GameCore* core)
{
	std::for_each(std::execution::par,draw_.begin(), draw_.end(), [&](DrawBasePtr& draw) {draw->SetFunc(core); });
}

