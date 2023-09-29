#pragma once
#include<string>
#include"../../../GeneralData.h"
#include"../CreateNumString.h"
#include <map>

/// <summary>
/// HitObj情報格納関数
/// ファイル読み込み用
/// </summary>
namespace GeneralLoadFunc
{
	struct CreateData
	{
		const std::string hedData;
		CreateData(const std::string hed):hedData(hed){};
		auto Getdata(const std::string& data)
		{
			 return CreateNumString()(data, hedData);
		}
	};

	struct AudioFilename:
		public CreateData
	{
		AudioFilename() :CreateData("AudioFilename:"){};
		bool operator()(Beat::General& general, const std::string& data)
		{
			auto result = Getdata(data);
			if (!result)
			{
				return false;
			}
			general.AudioFilename = result.value();

			auto num = general.AudioFilename.find_first_not_of(" ");

			general.AudioFilename.erase(0, num);

			return true;
		}
	};

	struct SampleSet :
		public CreateData
	{
		SampleSet() :CreateData("SampleSet:") {
			setData = {
				{"Normal",Beat::SampleSet::Normal},
				{"Soft",Beat::SampleSet::Soft},
				{"Drum",Beat::SampleSet::Drum}
			};
		};
		std::map<std::string, Beat::SampleSet> setData;
		bool operator()(Beat::General& general, const std::string& data)
		{
			auto result = Getdata(data);
			if (!result.has_value())
			{
				return false;
			}
			auto& key = result.value();
			//キーから余分な情報を外す
			key.replace(0,key.find_first_not_of(" "),"");
			if (setData.count(result.value()) == 0)
			{
				return false;
			}
			general.SampleSet = setData[result.value()];

			return true;
		}
	};

	struct AudioLeadIn :
		public CreateData
	{
		AudioLeadIn() :CreateData("AudioLeadIn:") {};
		bool operator()(Beat::General& general, const std::string& data)
		{
			auto result = Getdata(data);
			if (!result)
			{
				return false;
			}
			general.AudioLeadIn = static_cast<unsigned int>(std::stoi(result.value()));
			return true;
		}
	};
	
	struct PreviewTime :
		public CreateData
	{
		PreviewTime() :CreateData("PreviewTime:"){};
		bool operator()(Beat::General& general, const std::string& data)
		{
			auto result = Getdata(data);
			if (!result)
			{
				return false;
			}
			general.PreviewTime = static_cast<unsigned int>(std::stoi(result.value()));
			return true;
		}
	};

	struct Mode :
		public CreateData
	{
		Mode() :CreateData("Mode:") {};
		bool operator()(Beat::General& general, const std::string& data)
		{
			auto result = Getdata(data);
			if (!result)
			{
				return false;
			}
			general.Mode = static_cast<Beat::GameMode>(std::stoi(result.value()));
			return true;
		}
	};
}
