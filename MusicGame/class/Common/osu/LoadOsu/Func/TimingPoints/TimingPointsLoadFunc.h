#pragma once
#include<string>
#include<sstream>
#include<functional>
#include"../../../HitObj.h"

namespace
{
	using namespace Beat;
}

/// <summary>
/// HitObjèÓïÒäiî[ä÷êî
/// ÉtÉ@ÉCÉãì«Ç›çûÇ›óp
/// </summary>
namespace TimingPointsLoadFunc
{
	struct Time
	{
		bool operator()(TimingPoint& obj, const std::string& data)
		{
			obj.time = std::stoi(data);
			return true;
		}
	};
	struct BeatLength
	{
		bool operator()(TimingPoint& obj, const std::string& data)
		{
			obj.beatLength = std::stod(data);
			return true;
		}
	};

	struct Meter
	{
		bool operator()(TimingPoint& obj, const std::string& data)
		{
			obj.meter = std::stoi(data);
			return true;
		}
	};

	struct Volume
	{
		bool operator()(TimingPoint& obj, const std::string& data)
		{
			obj.volume = std::stoi(data);
			return true;
		}
	};

	struct Uninertied
	{
		bool operator()(Beat::TimingPoint& obj, const std::string& data)
		{
			obj.uninertied = std::stoi(data);
			return true;
		}
	};

	struct Effect
	{
		bool operator()(Beat::TimingPoint& obj, const std::string& data)
		{
			obj.effects = static_cast<Beat::TimingPoint::Effect>(std::stoi(data));
			return true;
		}
	};
	struct SampleSet
	{
		bool operator()(Beat::TimingPoint& obj, const std::string& data)
		{
			obj.sampleSet = static_cast<Beat::SampleSet>(std::stoi(data));
			return true;
		}
	};
	struct SampleIndex
	{
		bool operator()(Beat::TimingPoint& obj, const std::string& data)
		{
			obj.sampleIndex =std::stoi(data);
			return true;
		}
	};
	struct SetData
	{
		SetData()
		{
			setDataFuncVec_ =
			{
				std::bind_front(TimingPointsLoadFunc::Time()),
				std::bind_front(TimingPointsLoadFunc::BeatLength()),
				std::bind_front(TimingPointsLoadFunc::Meter()),
				std::bind_front(TimingPointsLoadFunc::SampleSet()),
				std::bind_front(TimingPointsLoadFunc::SampleIndex()),
				std::bind_front(TimingPointsLoadFunc::Volume()),
				std::bind_front(TimingPointsLoadFunc::Uninertied()),
				std::bind_front(TimingPointsLoadFunc::Effect()),
			};
		}


		bool operator()(TimingPoints& vec, const std::string& data)
		{
			if (data.find(',') == std::string::npos)
			{
				return false;
			}
			std::stringstream sData(data);
			std::string buf;
			Beat::TimingPoint result;
			int cnt = 0;
			while (std::getline(sData, buf, ','))
			{
				if (setDataFuncVec_.size() == cnt)
				{
					break;
				}
				auto& func = setDataFuncVec_[cnt];
				cnt++;
				if (func == nullptr)
				{
					continue;
				}
				func(result, buf);
			}
			vec.emplace_back(result);
			return true;
		}
	private:
		using setDataFunc = std::function<bool(TimingPoint&, const std::string&) > ;
		std::vector<setDataFunc> setDataFuncVec_;
	};
}



