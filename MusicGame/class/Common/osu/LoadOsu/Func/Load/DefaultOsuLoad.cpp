#include "DefaultOsuLoad.h"
#include "../Events/LoadEvent.h"
#include "../Difficulty/DifficultyLoad.h"
#include "../HitObj/HitObjLoad.h"
#include "../General/GeneralLoad.h"
#include"../Metadata/MetadataLoad.h"
#include"../TimingPoints/TimingPointsLoad.h"
#include"../Score/CreateScoreMag.h"

DefaultOsuLoad::DefaultOsuLoad(Beat::LoadDataPtr& loadData):
	OsuLoadBase(0,loadData)
{
	Init();
}

void DefaultOsuLoad::Init()
{
	loadModule_ =
	{
		new GeneralLoad(),
		new HitObjLoad(),
		new DifficultyLoad(),
		new EventLoad(),
		new MetadataLoad(),
		new TimingPointsLoad(),
		new CreateScoreMag(),
	};

}
