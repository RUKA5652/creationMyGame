#include "NotesMove.h"
#include<cmath>
#include"NoteData.h"
#include"../../LoadConfigData.h"
#include"../DecisionTransform.h"
#include"../Lane/LaneLength.h"
#include"../../../WindowSize.h"

#include<DxLib.h>
#include "../../../../../_debug/_DebugConOut.h"




NotesMove::NotesMove(Note::NotesDataPtr noteData, Beat::HitsDataPtr hitdata,
	LaneLengthConstPtr length, DecisionTransformConstPtr decisionData)
{
	hitdata_ = std::move(hitdata);
	noteData_ = std::move(noteData);
	length_ = std::move(length);
	decData_ = std::move(decisionData);
}

void NotesMove::Update(Timer::DeletaTimeConst& delta,const InputManager& input)
{
	Delet();

	//à⁄ìÆèàóù
	Move(delta);

}

bool NotesMove::GetEnd()
{
	return noteData_->empty();
}

void NotesMove::Delet()
{
	for (int i = 0; i < hitdata_->hitData_.size(); i++)
	{
		auto& hit = hitdata_->hitData_[i];
		if (i >= noteData_->normalsData.size())
		{
			break;
		}
		auto& normalNotes = noteData_->normalsData[i];
		DeletNormal(normalNotes,hit.normalsResult);
		auto& holdNotes = noteData_->holdsData[i];
		DeletHold(holdNotes, hit.holdsResult);
	}


}

void NotesMove::DeletNormal(std::deque<Note::NormalData>& laneNotes, const Beat::NormalHitsData& normalsResult)
{
	if (normalsResult.size() == 0)
	{
		return;
	}

	auto& windowY = lpWindowSize->GetSize().y;
	auto check = [normalsResult, windowY](Note::NormalData& note) {
		if (note.endTime > normalsResult.rbegin()->time)
		{
			return false;
		}
		for (auto& data : normalsResult)
		{
			if (note.endTime == data.time)
			{
				return true;
			}
		}
		return 	note.pos.y > windowY;
	};
	

	std::erase_if(laneNotes, check);
}

void NotesMove::DeletHold(std::deque<Note::HoldData>& laneNotes, const Beat::HoldHitData& holdsResult)
{
	if (laneNotes.size() == 0)
	{
		return;
	}
	auto& windowY = lpWindowSize->GetSize().y;
	auto check = [holdsResult, windowY](Note::HoldData& note) {
		if (!holdsResult)
		{
			return 	 note.ePos.y > windowY;
		}
		auto& data = holdsResult.value();
		if (note.sTime > data.sTime)
		{
			return false;
		}

		if (data.sTime == note.sTime && data.eTime == note.eTime)
		{
			if (note.ePos.y > windowY)
			{
				return true;
			}
			return data.endFlag ;
		}
		return 	 note.ePos.y > windowY;
	};

	std::erase_if(laneNotes, check);

}

void NotesMove::Move(const Beat::Time& nowTime)
{
	NormalMove(nowTime, noteData_->normalsData);
	HoldMove(nowTime, noteData_->holdsData);
}

void NotesMove::NormalMove(const Beat::Time& nowTime, Note::Normals& normalsData)
{
	//à⁄ìÆèàóù
	for (auto& laneNotes : normalsData)
	{
		for (auto& note : laneNotes)
		{
			auto result = std::lerp(0, decData_->GetOffset(),
				(static_cast<double>(nowTime) - note.generatTime) / (note.endTime - note.generatTime));
			note.pos.y = static_cast<int>(result);
		}
	}
}

void NotesMove::HoldMove(const Beat::Time& nowTime, Note::Holds& holdsData)
{
	//à⁄ìÆèàóù
	for (int i = 0; i < holdsData.size(); i++)
	{
		for (auto& note : holdsData[i])
		{
			auto result = std::lerp(0, decData_->GetOffset(),
				(static_cast<double>(nowTime) - note.generatTime) / (note.sTime - note.generatTime));
			note.sPos.y = static_cast<int>(result);

			auto eGeneTime = (note.eTime - note.sTime) + note.generatTime;
			result = std::lerp(0, decData_->GetOffset(),
				(static_cast<double>(nowTime) - eGeneTime) / (note.eTime - eGeneTime));
			note.ePos.y = static_cast<int>(result);

			if (hitdata_->hitData_[i].holdsResult)
			{
				if (hitdata_->hitData_[i].holdsResult.value().sTime == note.sTime &&
					hitdata_->hitData_[i].holdsResult.value().result != Beat::HitResult::Type::BAD)
				{

					note.sPos.y = decData_->GetOffset();
					note.holdTime = nowTime;

				}
				else if (note.holdTime != note.generatTime)
				{
					eGeneTime = (note.holdTime - note.sTime) + note.generatTime;
					result = std::lerp(0, decData_->GetOffset(),
						(static_cast<double>(nowTime) - eGeneTime) / (note.holdTime -eGeneTime));
					note.sPos.y = static_cast<int>(result);
				}
			}			
		}
	}
}

