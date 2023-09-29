#include "SelectUI.h"
#include"SelectUIDraw.h"

SelectUI::SelectUI()
	:ObjBase(0,1)
{
	draw_.emplace_back(std::make_shared<SelectUIDraw>());
}
