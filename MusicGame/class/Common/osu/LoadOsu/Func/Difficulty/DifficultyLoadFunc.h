#pragma once
#include<string>
#include<optional>
#include"../../../Difficulty.h"
#include"../CreateNumString.h"

namespace DifficultyLoadFunc
{
	struct DefHPDrainRate
	{
		const std::string hed = "HPDrainRate:";
		bool operator()(Beat::Difficulty& difficulty, const std::string& data)
		{
			auto numString = CreateNumString()(data, hed);
			if (!numString.has_value())
			{
				return false;
			}
			difficulty.HPDrainRate = std::stoi(numString.value().c_str());
			return true;
		}
	};

	struct DefCircleSize
	{
		const std::string hed = "CircleSize:";
		bool operator()(Beat::Difficulty& difficulty, const std::string& data)
		{
			auto numString = CreateNumString()(data, hed);
			if (!numString.has_value())
			{
				return false;
			}
			difficulty.CircleSize = max(4,std::stoi(numString.value()));
			return true;
		}
	};

	struct DefOverallDifficulty
	{
		const std::string hed = "OverallDifficulty:";
		bool operator()(Beat::Difficulty& difficulty, const std::string& data)
		{
			auto numString = CreateNumString()(data, hed);
			if (!numString.has_value())
			{
				return false;
			}
			difficulty.OverallDifficulty = std::stoi(numString.value().c_str());
			return true;
		}
	};

	struct DefApproachRate
	{
		const std::string hed = "ApproachRate:";
		bool operator()(Beat::Difficulty& difficulty, const std::string& data)
		{
			auto numString = CreateNumString()(data, hed);
			if (!numString.has_value())
			{
				return false;
			}
			difficulty.ApproachRate = std::stoi(numString.value());
			return true;
		}
	};

	struct DefSliderMultiplier
	{
		const std::string hed = "SliderMultiplier:";
		bool operator()(Beat::Difficulty& difficulty, const std::string& data)
		{
			auto numString = CreateNumString()(data, hed);
			if (!numString.has_value())
			{
				return false;
			}
			difficulty.SliderMultiplier = std::stof(numString.value());
			return true;
		}
	};

	struct DefSliderTickRate
	{
		const std::string hed = "SliderTickRate:";
		bool operator()(Beat::Difficulty& difficulty, const std::string& data)
		{
			auto numString = CreateNumString()(data, hed);
			if (!numString.has_value())
			{
				return false;
			}
			difficulty.SliderTickRate = std::stoi(numString.value());
			return true;
		}
	};
}



