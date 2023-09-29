#pragma once
#include"../../../Base/Update/UpdateBase.h"
#include<memory>
#include"NoteData.h"
#include"../DecisionData.h"
#include"../Lane/LaneLength.h"
#include"../DecisionTransform.h"



class NotesMove
	:public UpdateBase
{
public:
	NotesMove(Note::NotesDataPtr noteData, Beat::HitsDataPtr hitdata,
		 LaneLengthConstPtr length, DecisionTransformConstPtr decisionData);
	void Update(Timer::DeletaTimeConst& delta,const InputManager& input) override;

	bool GetEnd();

private:
	LaneLengthConstPtr length_;

	DecisionTransformConstPtr decData_;

	Note::NotesDataPtr noteData_;

	Beat::HitsDataConstPtr hitdata_;

	void Delet();

	void DeletNormal(std::deque<Note::NormalData>& laneNotes, const Beat::NormalHitsData& normalsResult);

	void DeletHold(std::deque<Note::HoldData>& laneNotes, const Beat::HoldHitData& holdsResult);


	void Move(const Beat::Time& nowTime);

	void NormalMove(const Beat::Time& nowTime,Note::Normals& normalsData);

	void HoldMove(const Beat::Time& nowTime, Note::Holds& holdsData);

};

