#pragma once
#include "InputManager.h"
/// <summary>
/// インプット作成クラス
/// </summary>
class BaseCreateInput
{
public:
	virtual void operator()(InputManagerPtr& ptr) = 0;

private:

};
