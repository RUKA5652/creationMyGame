#include "DifficultyLoad.h"
#include "DifficultyLoadFunc.h"

namespace
{
	constexpr auto title("[Difficulty]");
}

DifficultyLoad::DifficultyLoad():
	LoadSectionBase(title)
{
	Init();
}

bool DifficultyLoad::LoadFile(const std::string& fileData, Beat::LoadDataPtr data)
{
	return LoadSectionBase::LoadFile(fileData,data->difficulty);
}

void DifficultyLoad::Init()
{
	setDataFuncVec_ =
	{
		std::bind_front(DifficultyLoadFunc::DefHPDrainRate()),
		std::bind_front(DifficultyLoadFunc::DefHPDrainRate()),
		std::bind_front(DifficultyLoadFunc::DefCircleSize()),
		std::bind_front(DifficultyLoadFunc::DefOverallDifficulty()),
		std::bind_front(DifficultyLoadFunc::DefApproachRate()),
		std::bind_front(DifficultyLoadFunc::DefSliderMultiplier()),
		std::bind_front(DifficultyLoadFunc::DefSliderTickRate()),
	};
}


