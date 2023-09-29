#include "Lane.h"
#include"Draw/ObliqueLaneDraw.h"
#include"LaneLength.h"
#include"LaneDivision.h"
#include"../../LoadData.h"
#include"../../../Base/GameCore.h"
#include<DxLib.h>


Lane::Lane(Initialization& data)
	:ObjBase(0,1)
{
	draw_.emplace_back(std::make_shared<ObliqueLaneDraw>(data.division));
}

