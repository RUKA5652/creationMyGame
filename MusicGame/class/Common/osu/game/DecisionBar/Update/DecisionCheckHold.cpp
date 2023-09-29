#include "DecisionCheckHold.h"
#include "../../../../../Input/Game/GameSceneInputKey.h"
#include "../../../../../Input/EnumCast.h"
#include "../../../../../../_debug/_DebugConOut.h"



void DecisionCheckHold::Update(const InputManager::InputResult* inputResult, int laneNo, const Beat::Time& nowTime, Note::NotesDataConstPtr& notesData,
	Beat::HitsDataPtr& hitsData, Decision::AnimSetFunc& func, Decision::SetDrawFunc& drawFunc)
{
	if (CheckNowHorld(laneNo, nowTime,hitsData,inputResult,func, drawFunc))
	{
		return;
	}
	CheckHitStart(laneNo, nowTime,notesData, hitsData, inputResult, func, drawFunc);
}

bool DecisionCheckHold::CheckHitKey(const InputManager::InputResult* inputResult, int laneNo)
{
	return inputResult->at(laneNo).now;
}

bool DecisionCheckHold::CheckNowHorld(int laneNo, const Beat::Time& nowTime, Beat::HitsDataPtr& hitsData,
	const InputManager::InputResult* inputResult, Decision::AnimSetFunc& func, Decision::SetDrawFunc& drawFunc)
{
	auto& hits = hitsData->hitData_[laneNo].holdsResult;
	if (!hits)
	{
		return false;
	}
	auto& data = hits.value();
	UpdateNowHorld(data, inputResult, laneNo, nowTime, hitsData, func, drawFunc);
	if (data.eTime <= nowTime)
	{
		func(laneNo, false, Decision::AnimType::Holde);

		data.endFlag = true;
	}
	return true;
}


void DecisionCheckHold::UpdateNowHorld(Beat::HitResult::HoldResult& data, const InputManager::InputResult* inputResult, int laneNo,
	const Beat::Time& nowTime, Beat::HitsDataPtr& hitsData, Decision::AnimSetFunc& func, Decision::SetDrawFunc& drawFunc)
{
	/**/
	if (data.result == Beat::Type::BAD)
	{
		if (DecisionCheck::CheckHitKey(inputResult, laneNo))
		{
			data.result = Beat::Type::NON;
		}
		data.tupPoint = nowTime;
	}
	else
	{
		if (CheckHitKey(inputResult, laneNo))
		{
			data.holdTime = nowTime - data.tupPoint;
		}
		else
		{
			data.tupPoint = nowTime;
		}
	}
	/*/ //‚¨[‚Æ
	data.holdTime = nowTime - data.tupPoint;
	/**/

	while (nowTime >= data.checkEnd)
	{
		CheckHitTime(data, nowTime);
		/**/
		if (CheckHitKey(inputResult, laneNo))
		{
			data.holdTime = nowTime - data.checkEnd;
		}
		else
		{
			data.holdTime = 0;
		}

		/*/ //auto
		data.holdTime = nowTime - data.checkEnd;
		/**/
		if (data.result != Beat::Type::BAD)
		{
			drawFunc(data.result);
		}
		else
		{
			func(laneNo, false, Decision::AnimType::Holde);
		}
		ConboCount(hitsData, data.result);

		data.tupPoint = data.checkEnd;
		data.checkStart = data.checkEnd;
		data.checkEnd += score_->midpoint;
		if (data.checkEnd > data.eTime)
		{
			data.checkEnd = data.eTime;
		}
		if (data.checkStart == data.checkEnd)
		{
			break;
		}
	}
}

void DecisionCheckHold::CheckHitTime(Beat::HitResult::HoldResult& hold, const Beat::Time& nowTime)
{
	auto baseTime = score_->midpoint;
	if (baseTime >  hold.checkEnd - hold.checkStart)
	{
		baseTime =  hold.checkEnd - hold.checkStart;
	}
	hold.result = Beat::Type::BAD;
	if (hold.holdTime == 0)
	{
		return;
	}
	auto time = baseTime - hold.holdTime;
	for (auto& [type,checkTime] : checkHitTime_)
	{
		if (checkTime > time)
		{
			hold.result = type;
			return;
		}
	}

	


}


void DecisionCheckHold::CheckHitStart(int laneNo, const Beat::Time& nowTime, Note::NotesDataConstPtr& notesData, Beat::HitsDataPtr& hitsData,
	const InputManager::InputResult* inputResult, Decision::AnimSetFunc& func, Decision::SetDrawFunc& drawFunc)
{
	auto& hits = hitsData->hitData_[laneNo].holdsResult;

	auto& laneNotes = notesData->holdsData[laneNo];

	auto CheckKey = [&](int& subTime,const Note::HoldData& note) {
		if (DecisionCheck::CheckHitKey(inputResult, laneNo))
		{
			for (auto& checkData : checkHitTime_)
			{
				auto ptr = SetData(subTime, checkData, hits, nowTime, drawFunc, note, hitsData, func, laneNo);
				if (ptr != nullptr)
				{
					UpdateNowHorld(*ptr, inputResult, laneNo, nowTime, hitsData, func, drawFunc);
					return true;
				}
			}
		}
		return false;
	};


	for (auto& note : laneNotes)
	{
		auto subTime = static_cast<int>(note.sTime) - static_cast<int>(nowTime);
		if (CheckKey(subTime, note))
		{
			continue;
		}
		if (note.sTime + checkHitTime_.at(/**/Beat::Type::BAD /*/Beat::Type::JUST /**/) <= nowTime)
		{
			auto& result = hits.emplace(note.sTime, note.eTime, /**/Beat::Type::BAD /*/Beat::Type::JUST /**/, note.sound, 0,
				note.sTime,note.sTime + score_->midpoint, note.sTime, false);
			if (result.checkEnd > result.eTime)
			{
				result.checkEnd = result.eTime;
			}
			//drawFunc(result.result);
			ConboCount(hitsData, result.result);
		}

	}

}



Beat::HitResult::HoldResult* DecisionCheckHold::SetData(int subTime, std::pair<const Beat::HitResult::Type, Beat::Time>& checkData,
	Beat::HoldHitData& hits,const Beat::Time& nowTime, Decision::SetDrawFunc& drawFunc, const Note::HoldData& note, Beat::HitsDataPtr& hitsData,
	Decision::AnimSetFunc& func, int laneNo)
{
	if (checkData.first == Beat::HitResult::Type::BAD)
	{
		return nullptr;
	}
	if ( (subTime * subTime) >= checkData.second * checkData.second)
	{
		return nullptr;
	}
	if (hits)
	{
		return nullptr;
	}
	auto& result = hits.emplace(note.sTime, note.eTime, checkData.first, note.sound, 0, note.sTime, note.sTime + score_->midpoint, note.sTime, false);
	if (result.checkEnd > result.eTime)
	{
		result.checkEnd = result.eTime;
	}
	
	func(laneNo, true, Decision::AnimType::Holde);
	SoundPlay(note.sound);
	ConboCount(hitsData, result.result);
	drawFunc(checkData.first);
	return &result;

}