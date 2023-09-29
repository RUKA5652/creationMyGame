#pragma once
#include"DecisionCheck.h"
#include "../HitAnim/HitAnimEnum.h"
class DecisionCheckHold
	:public DecisionCheck
{
public:
	using DecisionCheck::DecisionCheck;
private:

	void Update(const InputManager::InputResult* inputResult, int laneNo, const Beat::Time& nowTime,
		Note::NotesDataConstPtr& notesData, Beat::HitsDataPtr& hitsData, Decision::AnimSetFunc& func, Decision::SetDrawFunc& drawFunc) override;

	bool CheckHitKey(const InputManager::InputResult* inputResult, int laneNo) override;

	bool CheckNowHorld(int laneNo, const Beat::Time& nowTime,Beat::HitsDataPtr& hitsData, 
		const InputManager::InputResult* inputResult, Decision::AnimSetFunc& func, Decision::SetDrawFunc& drawFunc);

	void UpdateNowHorld(Beat::HitResult::HoldResult& data, const InputManager::InputResult* inputResult,
		int laneNo, const Beat::Time& nowTime, Beat::HitsDataPtr& hitsData, Decision::AnimSetFunc& func, 
		Decision::SetDrawFunc& drawFunc);
	//ÉzÅ[ÉãÉhåãâ îªíË
	void CheckHitTime(Beat::HitResult::HoldResult& hold, const Beat::Time& nowTime);

	void CheckHitStart(int laneNo, const Beat::Time& nowTime, Note::NotesDataConstPtr& notesData, 
		Beat::HitsDataPtr& hitsData, const InputManager::InputResult* inputResult, Decision::AnimSetFunc& func, 
		Decision::SetDrawFunc& drawFunc);

	Beat::HitResult::HoldResult* SetData(int subTime, std::pair<const Beat::HitResult::Type, Beat::Time>& checkData,Beat::HoldHitData& hits, const Beat::Time& nowTime,
		Decision::SetDrawFunc& drawFunc, const Note::HoldData& note, Beat::HitsDataPtr& hitsData,Decision::AnimSetFunc& func, int laneNo);

};

