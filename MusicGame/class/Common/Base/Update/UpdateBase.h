#pragma once
#include<memory>
#include<vector>
#include<map>
#include<functional>
#include"../BaseData.h"
#include"../../../Timer/Timer.h"
#include "../../../Input/InputManager.h"

/// <summary>
/// 更新クラスベース
/// </summary>
class UpdateBase
{
public:

	virtual ~UpdateBase();
	virtual void Update(Timer::DeletaTimeConst& delta,const InputManager& input) = 0;

private:



};

using UpdateBasePtr = std::unique_ptr<UpdateBase>;
