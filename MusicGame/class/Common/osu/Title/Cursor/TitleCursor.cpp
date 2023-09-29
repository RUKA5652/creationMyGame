#include "TitleCursor.h"
#include"TitleCursorDraw.h"
#include"TitleCursorUpdate.h"
#include"CursorShareData.h"

TitleCursor::TitleCursor(std::shared_ptr<std::function<void(void)>> func)
	: ObjBase(1, 1)
{
	auto shareData = std::make_shared<CursorShareData>();
	draw_.emplace_back(std::make_shared<TitleCursorDraw>(shareData));
	update_.emplace_back(std::make_unique<TitleCursorUpdate>(shareData,func));
}

TitleCursor::~TitleCursor()
{
}
