#pragma once
#include "InputManager.h"
/// <summary>
/// �C���v�b�g�쐬�N���X
/// </summary>
class BaseCreateInput
{
public:
	virtual void operator()(InputManagerPtr& ptr) = 0;

private:

};
