#pragma once
#include"../../../Base/GameObjBase.h"
/// <summary>
/// �^�C�g���K�C�h
/// </summary>
class TitleCursor
	:public ObjBase
{
public:
	TitleCursor(std::shared_ptr<std::function<void(void)>> func);
	~TitleCursor();

private:
};

