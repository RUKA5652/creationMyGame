#include "LoadSkinImage.h"
#include<typeinfo>
#include<DxLib.h>
#include<regex>
#include<iostream>
#include"../FolderSearch.h"


LoadSkinImage::LoadSkinImage()
{
	CreateImageName();
}

Beat::SkinImageMap LoadSkinImage::LoadData(const std::string& fileName)
{
	Beat::SkinImageMap map;
	FolderSearch(std::bind_front(&LoadSkinImage::SetImage, this, std::ref(map)))(directory + fileName);
	return map;
}

void LoadSkinImage::LoadData(const std::string& fileName, Beat::SkinImageMap& map)
{
	FolderSearch(std::bind_front(&LoadSkinImage::SetImage,this, std::ref(map)))(directory + fileName);
}

void LoadSkinImage::CreateImageName()
{
	imageName_ =
	{
		{"notes1",Beat::SkinImageType::Notes1},
		{"notes2",Beat::SkinImageType::Notes2},
		{"notes5",Beat::SkinImageType::Notes5},
		{"hold1",Beat::SkinImageType::HoldLane1},
		{"hold2",Beat::SkinImageType::HoldLane2},
		{"hold5",Beat::SkinImageType::HoldLane5},
		{"lightingN",Beat::SkinImageType::NotesLighth},
		{"lightingL",Beat::SkinImageType::HoldLighth},
		{"lane",Beat::SkinImageType::Lane},
		{"just",Beat::SkinImageType::JUST},
		{"great",Beat::SkinImageType::Great},
		{"attack",Beat::SkinImageType::Good},
		{"bad",Beat::SkinImageType::Bad},
		{"score",Beat::SkinImageType::num},
		{"score-x",Beat::SkinImageType::scoreX},
		{"LigthLane",Beat::SkinImageType::LaneLighth},
		{"menu-button-background",Beat::SkinImageType::MusicFolder},
		{"DecisionBar",Beat::SkinImageType::DecisionBar},
		{"ranking-title",Beat::SkinImageType::Rank},
		{"star",Beat::SkinImageType::Level},
		//{"ranking-XH",Beat::SkinImageType::RankSSH},
		//{"ranking-SH",Beat::SkinImageType::RankSH},
		{"scorenum",Beat::SkinImageType::Score},
		{"ranking-XH",Beat::SkinImageType::RankSSH},
		{"ranking-X",Beat::SkinImageType::RankSS},
		{"ranking-SH",Beat::SkinImageType::RankSH},
		{"ranking-S",Beat::SkinImageType::RankS},
		{"ranking-A",Beat::SkinImageType::RankA},
		{"ranking-B",Beat::SkinImageType::RankB},
		{"ranking-C",Beat::SkinImageType::RankC},
		{"ranking-D",Beat::SkinImageType::RankD},
		{"pause-retry",Beat::SkinImageType::Retry},
		{"menu-back",Beat::SkinImageType::BACK},

	};
	
}



void LoadSkinImage::SetImage(Beat::SkinImageMap& map, const std::filesystem::path& path , std::string&& fileName)
{
	auto lastPos = fileName.find_last_of("-");
	auto filleNameIndex = lastPos == std::string::npos ? "" : fileName.substr(lastPos + 1);
	if (std::regex_search(filleNameIndex, std::regex(R"(\d)")))
	{
		fileName.replace(lastPos, fileName.size(), "");
	}
	//スモールがついてたら[1]に入れる
	std::string check = "-small";
	if (fileName.ends_with(check))
	{
		fileName.replace(fileName.size() - check.size() , fileName.size(), "");
		if (map[imageName_[fileName]].size() < 2)
		{
			map[imageName_[fileName]].resize(2,-1);
		}
		map[imageName_[fileName]][1] =  LoadGraph(path.string().c_str());
		return;
	}
	//[0]のデータが-1であれば初期化
	if (imageName_.count(fileName))
	{
		if (map[imageName_[fileName]].size() != 0 && map[imageName_[fileName]][0] == -1)
		{
			map[imageName_[fileName]][0] = LoadGraph(path.string().c_str());
			return;
		}
		map[imageName_[fileName]].emplace_back(LoadGraph(path.string().c_str()));
	}
}

