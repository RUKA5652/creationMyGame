#include "SpeedAdjust.h"
#include"Draw.h"
#include"Update.h"

SpeedAdjust::SpeedAdjust()
	:ObjBase(1,1)
{
	SideSpaceDivision sid;
	LaneLengthPtr length = std::make_shared<LaneLength>();
	LaneDivisionPtr div = std::make_shared<LaneDivision>(4, &sid, length);

	HitObjVecConstPtr objData;

	CreateNotes createNotes(objData, div, length);

	auto notesInit = createNotes.CreateInitData();


	update_.emplace_back(std::make_unique<SpeedAdjustUpdate>(notesInit));
	draw_.emplace_back(std::make_shared<SpeedAdjustDraw>(notesInit));
}
