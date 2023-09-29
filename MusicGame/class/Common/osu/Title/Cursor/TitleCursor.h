#pragma once
#include"../../../Base/GameObjBase.h"
/// <summary>
/// タイトルガイド
/// </summary>
class TitleCursor
	:public ObjBase
{
public:
	TitleCursor(std::shared_ptr<std::function<void(void)>> func);
	~TitleCursor();

private:
};

