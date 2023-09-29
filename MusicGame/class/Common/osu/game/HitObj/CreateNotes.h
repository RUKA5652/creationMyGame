#pragma once
#include"../../../Base/SetUp/CreateSupport.h"
#include"../HitObj/Notes.h"
#include"../Lane/LaneDivision.h"
#include"../Lane/LaneLength.h"
#include"../../../../Scene/GameScene.h"

class DecisionTransform;

class CreateNotes
	:public CreateSupport<Notes::Initialization, Notes>
{
public:


	CreateNotes(HitObjVecConstPtr objData,
		LaneDivisionPtr division, LaneLengthPtr length);

	~CreateNotes();
	Notes::Initialization* CreateInitData() override;
	//null‚ª•Ô‚é
	ObjBasePtr CreateObj() override;

	ObjBasePtr CreateObj(std::function<void(void)> func);

private:
	HitObjVecConstPtr objData_;
};

