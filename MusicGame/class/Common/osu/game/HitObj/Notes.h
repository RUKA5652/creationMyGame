#pragma once
#include<memory>
#include"../../../../Scene/GameScene.h"
#include"../../../Base/GameObjBase.h"
#include"../../HitObj.h"
#include"../DecisionData.h"
#include"NoteData.h"
#include"NotesDraw.h"
#include "../NoteSizeRatio.h"
#include "../DecisionTransform.h"
#include "../Lane/LaneLength.h"
#include "../Lane/LaneDivision.h"



class Notes:
	public ObjBase
{
public:
	struct Initialization
	{
		Note::NotesDataPtr noteData;
		NoteSizeRatioPtr noteSize;
		Beat::HitsDataPtr hitdata;
		const LaneDivisionPtr division;
		const LaneLengthPtr length;
		DecisionTransformPtr decisionData;
	};

	Notes(HitObjVecConstPtr objData,Initialization& initData, std::function<void(void)> func);

	void SetUpGraphic();



private:

	void Init();




};

