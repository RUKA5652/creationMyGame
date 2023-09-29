#include "Reel.h"
#include"../../../Base/GameCore.h"
#include"ReelData.h"
#include"Data/LoadReelData.h"
#include"ReelDraw.h"
#include"Data/SortReelData.h"
#include"ReelUpdate.h"


Reel::Reel(Beat::ReelDataPtr reelData, ReelSound* reelSound, const ChengeSceneFunc::CreateGameFunc& func)
	:ObjBase(1,1)
{
	reelData_ = reelData;
	update_.emplace_back(std::make_unique<ReelUpdate>(reelData_, reelSound, animData_,func));
	draw_.emplace_back(std::make_shared<ReelDraw>(reelData_, animData_));
}

Reel::~Reel()
{

}

