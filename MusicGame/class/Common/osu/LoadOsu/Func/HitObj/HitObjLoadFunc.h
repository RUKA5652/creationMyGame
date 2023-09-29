#pragma once
#include<string>
#include<sstream>
#include"../../../HitObj.h"

namespace
{
	using namespace Beat;
}

/// <summary>
/// HitObj情報格納関数
/// ファイル読み込み用
/// </summary>
namespace HitObjLoadFunc
{
	struct DefLine
	{
		bool operator()(Beat::HitObj& obj, const std::string& data)
		{
			obj.line = std::stoi(data);
			return true;
		}
	};
	struct DefNonData
	{
		bool operator()(Beat::HitObj& obj, const std::string& data)
		{
			return true;
		}
	};

	struct DefTime
	{
		bool operator()(Beat::HitObj& obj, const std::string& data)
		{
			obj.time = std::stoi(data);
			return true;
		}
	};

	struct DefTouch
	{
		bool operator()(Beat::HitObj& obj, const std::string& data)
		{
			obj.type = std::stoi(data);
			return true;
		}
	};

	struct DefSound
	{
		bool operator()(Beat::HitObj& obj, const std::string& data)
		{
			obj.sound = static_cast<Sound::Type>(std::stoi(data));
			return true;
		}
	};

	struct Params
	{
		bool operator()(Beat::HitObj& obj, const std::string& data)
		{
			if (obj.type & static_cast<Touch::Type>(Touch::TypeMode::ManiaHold))
			{
				obj.holdEndTime = std::stoi(data);
			}
			else
			{
				obj.holdEndTime = 0;
			}
			return true;
		}
	};

	struct SetData
	{
		SetData()
		{
			setDataFuncVec_ =
			{
				std::bind_front(HitObjLoadFunc::DefLine()),
				nullptr,
				std::bind_front(HitObjLoadFunc::DefTime()),
				std::bind_front(HitObjLoadFunc::DefTouch()),
				std::bind_front(HitObjLoadFunc::DefSound()),
				std::bind_front(HitObjLoadFunc::Params()),
			};
		}


		bool operator()(HitObjVec& vec, const std::string& data)
		{
			if (data.find(',') == std::string::npos)
			{
				return false;
			}
			std::stringstream sData(data);
			std::string buf;
			Beat::HitObj result;
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
		using setDataFunc = std::function<bool(Beat::HitObj&, const std::string&)>;
		std::vector<setDataFunc> setDataFuncVec_;
	};
}



