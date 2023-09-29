#pragma once
#include <fstream>
#include<filesystem>
#include<optional>
#include "../../rapidjson/writer.h"
#include"../../rapidjson/ostreamwrapper.h"
#include"../../rapidjson/istreamwrapper.h"
#include "../../rapidjson/document.h"

/// <summary>
/// ファイルpath
/// </summary>
namespace IOJSON
{
	constexpr const char* filePath = "resource/sauce/";
}
/// <summary>
/// JSON吐き出し
/// </summary>
struct OutPutJSON
{
	bool operator()(const rapidjson::Document& root,const char* name)
	{
		std::filesystem::create_directories(IOJSON::filePath);
		std::ofstream ofs((std::string)IOJSON::filePath + name +".json",std::ios::out);
		if (!ofs)
		{
			return false;
		}
		rapidjson::OStreamWrapper osw(ofs);
		rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
		root.Accept(writer);
		return true;
	}
};
/// <summary>
/// JSON読み込み
/// </summary>
struct InPutJSON
{
	std::optional<rapidjson::Document> operator()(const char* name)
	{
		std::filesystem::create_directories(IOJSON::filePath);
		std::ifstream ifs((std::string)IOJSON::filePath + name + ".json");
		if (!ifs)
		{
			return std::nullopt;
		}
		rapidjson::IStreamWrapper ifw(ifs);
		rapidjson::Document root;
		root.ParseStream(ifw);
		return root;
	}
};