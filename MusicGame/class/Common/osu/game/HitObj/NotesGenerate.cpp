#include "NotesGenerate.h"
#include"../Lane/Lane.h"
#include"../Lane/LaneDivision.h"
#include"../DecisionTransform.h"
#include"../NoteSizeRatio.h"
#include"../../LoadConfigData.h"
#include"../../Skin/Image/SkinImage.h"
#include"GetPriorTime.h"

constexpr double msClock = 0.016;
constexpr int playfield = 512;

NotesGenerate::NotesGenerate(HitObjVecConstPtr data, LaneDivisionConstPtr division,
	DecisionTransformConstPtr decisionData, Note::NotesDataPtr noteData, NoteSizeRatioPtr noteRatio)
{
	hitObjvec_ = std::move(data);
	noteRatio_ = std::move(noteRatio);
	noteData_ = std::move(noteData);
	division_ = std::move(division);
	decisionData_ = std::move(decisionData);
	Init();
}

NotesGenerate::~NotesGenerate()
{
}


 void NotesGenerate::Update(Timer::DeletaTimeConst& delta,const InputManager& input)
{
	int generateCnt = 0;
	while (CheckGenerate(delta))
	{
		generateCnt++;
	}

	if (generateCnt > 0)
	{
		CreateNote(generateCnt, delta);
	}
}

 bool NotesGenerate::GetEnd()
 {
	 const auto& objVec = *hitObjvec_;
	 return objVec.size() <= nowIndex_;
 }




void NotesGenerate::Init()
{
	nowIndex_ = 0;

}

bool NotesGenerate::CheckGenerate(const Beat::Time& nowTime)
{
	const auto& objVec = *hitObjvec_;
	if(objVec.size() <= nowIndex_)
	{
		return false;
	}
	const auto& hitObj = objVec[nowIndex_];

	auto priorTime = GetPriorTime()(decisionData_->GetOffset());

	if (hitObj.time > nowTime + static_cast<Beat::Time>(priorTime))
	{
		return false;
	}
	nowIndex_++;
	return true;
}

void NotesGenerate::CreateNote(int cnt, const Beat::Time& nowTime)
{
	const auto& objVec = *hitObjvec_;
	for (int i = cnt; i != 0; i--)
	{
		auto obj = &objVec[nowIndex_ - i];
		auto index = CreateLaneIndex(obj->line);
		if (noteData_->normalsData.size() > index)
		{
			if (obj->type  & static_cast<Beat::Touch::Type>(Beat::Touch::TypeMode::ManiaHold) )
			{
				SetHoldData(*obj, index);
				continue;
			}
			SetNormalData(*obj,index);
		}
	}
}



void NotesGenerate::SetNormalData(const Beat::HitObj& obj, const int& index)
{
	Beat::Time geneTime = obj.time - static_cast<Beat::Time>(GetPriorTime()(decisionData_->GetOffset()));
	auto& result = noteData_->normalsData[index].emplace_back(geneTime,obj.time);
	result.sound = obj.sound;
	result.lane = index;
	SetTransform(result, index);
}

void NotesGenerate::SetHoldData(const Beat::HitObj& obj, const int& index)
{
	Beat::Time geneTime = obj.time - static_cast<Beat::Time>(GetPriorTime()(decisionData_->GetOffset()));
	auto& result = noteData_->holdsData[index].emplace_back(geneTime);
	result.sTime = obj.time;
	result.eTime = obj.holdEndTime;
	result.sound = obj.sound;
	result.lane = index;
	SetTransform(result, index);
}


void NotesGenerate::SetTransform(Note::NormalData& note,const int& index)
{
	auto& lane = division_->GetBoxVec();
	if (lane.size() > index)
	{
		auto& box = lane.at(index);
		note.pos = box.LT;
	}
}

void NotesGenerate::SetTransform(Note::HoldData& note, const int& index)
{
	auto& lane = division_->GetBoxVec();
	if (lane.size() > index)
	{
		auto& box = lane.at(index);
		note.sPos = box.LT;
		note.ePos = box.LT;
	}
}

int NotesGenerate::CreateLaneIndex(Beat::Line line)
{
	return static_cast<int>(line * division_->GetBoxVec().size()) / playfield;
}

