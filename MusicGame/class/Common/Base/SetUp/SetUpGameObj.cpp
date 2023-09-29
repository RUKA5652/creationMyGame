#include "SetUpGameObj.h"
#include"../GameCore.h"
#include<algorithm>
#include<iterator>
#include <execution>
#include "../../../../_debug/_DebugConOut.h"


void SetUpGameObj::Add()
{
	if (core_ == nullptr)
	{
		throw;
		return;
	}

	std::for_each(std::execution::par, objData_.begin(), objData_.end(), [&](ObjBasePtr& obj) {obj->SetDraw(core_); });

	std::ranges::move(objData_,std::back_inserter(core_->objData_));
}

void SetUpGameObj::SetGameCore(GameCore* core)
{
	core_ = core;
}

void SetUpGameObj::SetGameObj(ObjBasePtr obj)
{
	objData_.emplace_back(std::move(obj));
}

void SetUpGameObj::SetObjCore()
{
	Add();
}

SetUpGameObj::~SetUpGameObj()
{
	TRACE("SetUpGameObj‰ð•ú\n");
}

void SetUpGameObj::SetUp(GameCore* core)
{
	SetGameCore(core);
	MakeObj();
	SetObjCore();
}


