#include "Update.h"
#include "../LoadConfigData.h"
#include"../game/HitObj/GetPriorTime.h"
#include "../../../Input/EnumCast.h"
#include"../../../Input/SpeedAdjust/SpeedAdjustInput.h"
#include"../../../JsonParam/IOJSON.h"


/// <summary>
/// JSONで使用するデータ
/// </summary>
inline namespace JSON
{
	//ファイル名前
	constexpr const char* FileName = "SpeedAdjust";
	//キー
	constexpr const char* NoteTime = "NoteJeneMs";
}



SpeedAdjustUpdate::SpeedAdjustUpdate(Notes::Initialization* init)
	:speed_(lpConfigData->GetConfigChangeData().ManiaSpeed)
{
	decisionData_ = init->decisionData;
	notesData_ = init->noteData;
	division_ = init->division;
	
	Load();
	CreateEndTime();
	CreateNote();

	nowTime_ = -static_cast<int>(GetPriorTime()(decisionData_->GetOffset(), speed_));

}

void SpeedAdjustUpdate::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	nowTime_ += delta;

	for (auto& laneNotes : notesData_->normalsData)
	{
		for (auto& note : laneNotes)
		{
			auto result = std::lerp(0, decisionData_->GetOffset(),
				(static_cast<double>(nowTime_) - note.generatTime) / (note.endTime - note.generatTime));
			note.pos.y = static_cast<int>(result);
		}
	}

	auto& key = input.GetInputData();
	bool change = false;
	if (key.at(Cast(SPEEDADJUST::UP)).oneShot())
	{
		change = true;
		speed_++;
	}
	if (key.at(Cast(SPEEDADJUST::DOWN)).oneShot())
	{
		change = true;
		speed_--;
		speed_ = max(1, speed_);
	}


	if (nowTime_ >= endTime_[endTime_.size() - 1] || change)
	{	
		nowTime_ = -static_cast<int>(GetPriorTime()(decisionData_->GetOffset(), speed_));
		CreateNote();
	}
}

void SpeedAdjustUpdate::CreateEndTime()
{
	for (int i = 0; i < endTime_.size(); i++)
	{
		endTime_[i] = static_cast<int>(noteTime_ *(i+1));
	}

}

void SpeedAdjustUpdate::CreateNote()
{
	
	auto& lane = division_->GetBoxVec();

	auto time = static_cast<int>(GetPriorTime()(decisionData_->GetOffset(), speed_));
	for (int i = 0; i < endTime_.size(); i++)
	{
		notesData_->normalsData[i].clear();
		auto& note = notesData_->normalsData[i].emplace_back(endTime_[i] - time, endTime_[i]);
		auto& box = lane.at(i);
		note.lane = i;
		note.pos = box.LT;
	}


}

void SpeedAdjustUpdate::Load()
{
	//JSONデータ読み込み
	auto result = InPutJSON()(FileName);
	//格納
	if (result)
	{
		auto& doc = result.value();
		noteTime_ = doc[NoteTime].GetFloat();
	}
}
