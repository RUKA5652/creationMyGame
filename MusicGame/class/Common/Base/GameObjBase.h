#pragma once
#include<memory>
#include"Draw/DrawBase.h"
#include"Update/UpdateBase.h"
#include "../../Timer/Timer.h"

class SetUpGameObj;
class GameCore;
class BaseData;


class ObjBase
{
public:


	ObjBase(size_t updateNum,size_t drawNum);
	virtual ~ObjBase();


	virtual void Update(Timer::DeletaTimeConst& delta,const InputManager& input);

protected:

	std::vector<UpdateBasePtr> update_;

	std::vector<DrawBasePtr> draw_;

	virtual void SetDraw(GameCore* core) ;

	friend SetUpGameObj;
};

using ObjBasePtr = std::unique_ptr<ObjBase>;

