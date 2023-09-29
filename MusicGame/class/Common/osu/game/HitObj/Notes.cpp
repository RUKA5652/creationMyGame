#include "Notes.h"
#include"../Lane/Lane.h"
#include"../Lane/LaneDivision.h"
#include"../../../Base/GameCore.h"
#include"NotesUpdate.h"

Notes::Notes(HitObjVecConstPtr objData, Initialization& initData, std::function<void(void)> func)
	:ObjBase(1,1)
{
	Init();
	
	update_.emplace_back(std::make_unique<NotesUpdate>(objData, initData, func));
	draw_.emplace_back(std::make_shared<NotesDraw>(initData.division,initData.noteData, initData.noteSize, initData.hitdata));
	
}

void Notes::SetUpGraphic()
{

}


void Notes::Init()
{

}