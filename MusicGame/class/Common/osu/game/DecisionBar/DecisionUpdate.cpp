#include "DecisionUpdate.h"
#include<DxLib.h>
#include<thread>
#include<functional>
#include"../DecisionTransform.h"
#include"../../../WindowSize.h"
#include"../../../../Input/Game/GameSceneInputKey.h"
#include"../../../../Input/EnumCast.h"
#include"Update/DecisionCheckHold.h"
#include"Update/DecisionChekNormal.h"
#include"../../Skin/Sound/SkinSound.h"
#include"Sound/DecisionCreateSound.h"

inline const char* filePass_ = "resource";

DecisionUpdate::DecisionUpdate(Beat::HitsDataPtr hitsData, DecisionTransformConstPtr data, 
	Note::NotesDataConstPtr notesData, Beat::LoadDataCPtr loadData,
	std::shared_ptr<Decision::AnimSetFunc> animSetFunc,Decision::SetDrawFuncPtr drawSetFunc)
	:hitsData_(hitsData),setAnim_(animSetFunc),drawSetFunc_(drawSetFunc)
{
	notesData_ = std::move(notesData);
	timingPointsPtr_ = loadData->timingPoints;
	SetCheckHitTime();
	SetCheckClass(loadData);
}

DecisionUpdate::~DecisionUpdate()
{
	for (auto& [key,soundSetData] : soundData_)
	{
		for (auto& [key, soundData] : soundSetData)
		{
			for (auto& [key, handleVec] : soundData)
			{
				for (auto& data : handleVec)
				{
					DeleteSoundMem(data);
				}
			}
		}
	}
}

void DecisionUpdate::Update(Timer::DeletaTimeConst& delta,const InputManager& input)
{
	auto time = delta;
	auto& inputData = input.GetInputData();
	for (auto& data : hitsData_->hitData_)
	{
		data.clear();
	}
	for (auto& checkClass : check_)
	{
		for (int i = 0; i < hitsData_->hitData_.size(); i++)
		{
			if (i >= notesData_->normalsData.size())
			{
				return;
			}
			checkClass->Update(&inputData, i, delta, notesData_, hitsData_, *setAnim_, *drawSetFunc_);
		}
	}
}

void DecisionUpdate::DebugDraw()
{
	//Checkhit();
}


void DecisionUpdate::LoadLimitTime()
{
}

void DecisionUpdate::SetCheckHitTime()
{
	//ƒ~ƒŠ•b‚ÅÝ’è 1/1000
	checkHitTime_ =
	{	
		{Beat::Type::BAD,132},
		{Beat::Type::GOOD,99},
		{Beat::Type::GREAT,66},
		{Beat::Type::JUST,33},
	};
}

void DecisionUpdate::SetCheckClass(Beat::LoadDataCPtr& loadData)
{
	CreateSoundData(loadData);
	nowTimingPoint_ = timingPointsPtr_->begin();
	check_ = {
		std::make_unique<DecisionCheckHold>(checkHitTime_,soundData_,nowTimingPoint_,
		loadData->generalData->SampleSet,loadData->scoreMagData),
		std::make_unique<DecisionChekNormal>(checkHitTime_,soundData_,nowTimingPoint_,
		loadData->generalData->SampleSet,loadData->scoreMagData)
	};
}

void DecisionUpdate::CreateSoundData(Beat::LoadDataCPtr& loadData)
{
	soundData_ = DecisionCreateSound()(loadData->folderPath);
}

