#pragma once
#include"DecisionCheck.h"

class DecisionChekNormal
	:public DecisionCheck
{
public:
	using DecisionCheck::DecisionCheck;

private:

	void CheckHit(const InputManager::InputResult* inputResult, int laneNo, int subTime, Beat::NormalHitsData& hits,
		Decision::SetDrawFunc& drawFunc, const Note::NormalData& note, Beat::HitsDataPtr& hitsData, Decision::AnimSetFunc& func);

	void CheckHitOut(const InputManager::InputResult* inputResult, int laneNo, int subTime, Beat::NormalHitsData& hits,
		Decision::SetDrawFunc& drawFunc, const Note::NormalData& note, Beat::HitsDataPtr& hitsData, Decision::AnimSetFunc& func);




	void Update(const InputManager::InputResult* inputResult, int laneNo, const Beat::Time& nowTime,
		Note::NotesDataConstPtr& notesData, Beat::HitsDataPtr& hitsData, Decision::AnimSetFunc& func, Decision::SetDrawFunc& drawFunc)  override;

	bool SetData(int subTime, std::pair<const Beat::HitResult::Type, Beat::Time>& checkData, Beat::NormalHitsData& hits,
		Decision::SetDrawFunc& drawFunc, const Note::NormalData& note, Beat::HitsDataPtr& hitsData, Decision::AnimSetFunc& func, int laneNo);



};

