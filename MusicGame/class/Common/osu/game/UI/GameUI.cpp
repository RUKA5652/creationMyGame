#include "GameUI.h"
#include"GameUIDraw.h"

GameUI::GameUI(LaneDivisionConstPtr division, DecisionTransformConstPtr data)
	:ObjBase(0,1)
{
	draw_.emplace_back(std::make_shared<GameUIDraw>(division,data));
}
