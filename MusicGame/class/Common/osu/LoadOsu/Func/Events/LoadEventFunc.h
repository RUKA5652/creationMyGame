#pragma once
#include<string>
#include<sstream>
#include<regex>
#include"../../../HitObj.h"

/// <summary>
/// HitObj情報格納関数
/// ファイル読み込み用
/// </summary>
namespace LoadEventFunc
{

	struct Background
	{
		//バックグラウンド構文: 0,0,filename,xOffset,yOffset
		std::optional<Beat::Events::BackImage> Check(const std::string& data)
		{
			std::stringstream sData(data);
			if (!FirstCheck(sData))
			{
				return std::nullopt;
			}
			std::string imagePass;
			std::getline(sData, imagePass, ',');
			std::erase(imagePass, '"');

			auto x = CheckInt(sData);
			if (!x.has_value())
			{
				return  std::nullopt;
			}
			auto y = CheckInt(sData);
			if (!y.has_value())
			{
				return  std::nullopt;
			}

			return Beat::Events::BackImage{ imagePass ,x.value(),y.value()};
		}

		bool FirstCheck(std::stringstream& sData)
		{
			std::string buf;
			std::string firstCheck;
			std::getline(sData, buf, ',');
			firstCheck = buf;
			std::getline(sData, buf, ',');
			firstCheck += buf;
			return firstCheck == "00";
		}

		std::optional<int> CheckInt(std::stringstream& sData)
		{
			std::string buf;
			std::getline(sData, buf, ',');
	/*		std::smatch result;
			if (!std::regex_match(buf,result,std::regex(R"(\d)")))
			{
				return std::nullopt;
			}*/
			return std::stoi(buf);
		}


		bool operator()(Beat::Events& events, const std::string& data)
		{
			auto cnt = std::ranges::count_if(data, [](const char& data) {return data == ','; });
			if (cnt != 4)
			{
				return false;
			}
			auto result = Check(data);
			if (!result)
			{
				return false;
			}
			*events.image_ = result.value();
			return true;
		}
	private:
	};
}



