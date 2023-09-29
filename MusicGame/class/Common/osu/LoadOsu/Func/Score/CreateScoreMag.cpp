#include "CreateScoreMag.h"




CreateScoreMag::CreateScoreMag()
{
	scoreLevel_ =
	{
		4000,
		2000,
		1000,
		750,
		700,
		650,
		600,
		550,
		500,
		450,
		400,
		350,
		300,
		250,
		200,
	};
}

bool CreateScoreMag::LoadFile(const std::string& fileData, Beat::LoadDataPtr data)
{
    if (!(data->scoreMagData && data->timingPoints && data->hitObjVec))
    {
        return false;
    }
	if (data->timingPoints->size() == 0)
	{
		return false;
	}
    data->scoreMagData->midpoint = CreateMidpoint(data->timingPoints);
	data->scoreMagData->maxCombo = MaxConboCount(data->hitObjVec, data->scoreMagData->midpoint);
	CreateMagData(*data->scoreMagData);
	CreateLevel(*data->scoreMagData);

    return true;
}

Beat::Time CreateScoreMag::CreateMidpoint(TimingPointsPtr& timingPoint)
{
	auto& point = *timingPoint->begin();
	auto bpm = 1 / point.beatLength * 1000 * 60;
	Beat::Time midpoint = static_cast<Beat::Time>((point.beatLength * point.meter) / 8);
	if (bpm < 120)
	{
		midpoint = static_cast<Beat::Time>((point.beatLength * point.meter) / 16) ;
	}
	if (bpm > 240)
	{
		midpoint = static_cast<Beat::Time>((point.beatLength * point.meter) / 4) ;
	}
	return midpoint;
}

int CreateScoreMag::MaxConboCount(HitObjVecPtr& data, Beat::Time midpoint)
{
	using namespace Beat;

	int cnt = 0;

	for (auto& obj : *data.get())
	{
		if (obj.type == static_cast<Touch::Type>(Touch::TypeMode::ManiaHold))
		{
			auto time = obj.holdEndTime - obj.time;
			auto midCont = time / midpoint;
			if (time % midpoint != 0)
			{
				midCont ++;
			}
			midCont ++;
			cnt += midCont;
		}
		else
		{
			cnt++;
		}
	}


	return cnt;
}

void CreateScoreMag::CreateMagData(Beat::ScoreMagData& magData)
{
	using namespace Beat;
	double baseScore = static_cast<double>(maxScore) / magData.maxCombo;
	magData.scoreMagData =
	{
		{Type::JUST,baseScore * 1.01},
		{Type::GREAT,baseScore },
		{Type::GOOD,baseScore *0.5},
	};
}

void CreateScoreMag::CreateLevel(Beat::ScoreMagData& magData)
{
	using namespace Beat;
	auto score = maxScore / Beat::maxLevel;
	auto baseScore = magData.scoreMagData[Beat::Type::GREAT];
	magData.level = static_cast<int>(scoreLevel_.size());
	for (int i = 0; i < static_cast<int>(scoreLevel_.size()); i++)
	{
		if (baseScore > scoreLevel_[i])
		{
			magData.level =  i++;
			return;
		}
	}


}


