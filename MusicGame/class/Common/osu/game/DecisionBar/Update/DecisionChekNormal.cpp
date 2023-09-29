#include "DecisionChekNormal.h"
#include "../../../../WindowSize.h"
#include "../HitAnim/HitAnimEnum.h"


void DecisionChekNormal::CheckHit(const InputManager::InputResult* inputResult, int laneNo, int subTime, Beat::NormalHitsData& hits, Decision::SetDrawFunc& drawFunc, const Note::NormalData& note, Beat::HitsDataPtr& hitsData, Decision::AnimSetFunc& func)
{
	if (CheckHitKey(inputResult, laneNo))
	{
		for (auto& checkData : checkHitTime_)
		{
			if (SetData(subTime, checkData, hits, drawFunc, note, hitsData, func, laneNo))
			{
				break;
			}
		}
	}
}


void DecisionChekNormal::CheckHitOut(const InputManager::InputResult* inputResult, int laneNo, int subTime,
	Beat::NormalHitsData& hits, Decision::SetDrawFunc& drawFunc, const Note::NormalData& note, Beat::HitsDataPtr& hitsData, Decision::AnimSetFunc& func)
{
	std::pair<const Beat::HitResult::Type, Beat::Time> checkData ={
		Beat::Type::JUST, checkHitTime_.at(Beat::Type::JUST) };

	SetData(subTime, checkData, hits, drawFunc, note, hitsData, func, laneNo);

}




void DecisionChekNormal::Update(const InputManager::InputResult* inputResult, int laneNo, const Beat::Time& nowTime,
	Note::NotesDataConstPtr& notesData, Beat::HitsDataPtr& hitsData, Decision::AnimSetFunc& func, Decision::SetDrawFunc& drawFunc)
{	
	auto windowY = lpWindowSize->GetSize().y;
	auto& hits = hitsData->hitData_[laneNo].normalsResult;
	auto& laneNotes = notesData->normalsData[laneNo];
	for (auto& note : laneNotes)
	{
		auto subTime = static_cast<int>(note.endTime) - static_cast<int>(nowTime);

		/** //auto
		CheckHitOut(inputResult, laneNo, subTime, hits, drawFunc, note, hitsData, func);
		/*/
		CheckHit(inputResult, laneNo, subTime, hits, drawFunc, note, hitsData, func);
		/**/
		if (note.endTime + checkHitTime_.at(Beat::Type::BAD) <= nowTime)
		{
			auto& result = hits.emplace_back(note.endTime, Beat::Type::BAD);
			ConboCount(hitsData, result.result);
		}
	}
}

bool DecisionChekNormal::SetData(int subTime, std::pair<const Beat::HitResult::Type, Beat::Time>& checkData, Beat::NormalHitsData& hits, Decision::SetDrawFunc& drawFunc, const Note::NormalData& note, Beat::HitsDataPtr& hitsData, Decision::AnimSetFunc& func, int laneNo)
{
	if ((subTime * subTime) < checkData.second * checkData.second)
	{
		if (hits.size() != 0)
		{
			if (!(hits[0].result == Beat::Type::JUST &&
				checkData.first == Beat::Type::JUST))
			{
				return true;
			}
		}
		drawFunc(checkData.first);
		auto& result = hits.emplace_back(note.endTime, checkData.first);
		ConboCount(hitsData, result.result);
		func(laneNo, true, Decision::AnimType::Normal);
		SoundPlay(note.sound);
		return true;
	}
	return false;
}

