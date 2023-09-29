#pragma once
#include"../../../Base/Update/UpdateBase.h"
#include "../../HitObj.h"
#include "NoteData.h"
#include"../Lane/LaneDivision.h"
#include"../DecisionTransform.h"
#include"../NoteSizeRatio.h"



class NotesGenerate
	:public UpdateBase
{
public:
	NotesGenerate(HitObjVecConstPtr data, LaneDivisionConstPtr division,
		DecisionTransformConstPtr decisionData, Note::NotesDataPtr noteData, NoteSizeRatioPtr noteRatio);
	~NotesGenerate();
	void Update(Timer::DeletaTimeConst& delta,const InputManager& input) override;

	bool GetEnd();

private:
	Note::NotesDataPtr noteData_;

	LaneDivisionConstPtr division_;
	DecisionTransformConstPtr decisionData_;

	NoteSizeRatioPtr noteRatio_;

	HitObjVecConstPtr hitObjvec_;


	int nowIndex_;

	void Init();

	bool CheckGenerate(const Beat::Time& nowTime);

	void CreateNote(int cnt, const Beat::Time& nowTime);

	void SetNormalData(const Beat::HitObj& obj,const int& index);

	void SetHoldData(const Beat::HitObj& obj,const int& index);


	void SetTransform(Note::NormalData& note, const int& index);

	void SetTransform(Note::HoldData& note, const int& index);

	int CreateLaneIndex(Beat::Line line);


};

