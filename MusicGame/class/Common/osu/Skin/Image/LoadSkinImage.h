#pragma once
#include<string>
#include<filesystem>
#include <map>
#include"SkinImageData.h"
#include "../DefaultPath.h"

class LoadSkinImage
{
public:

	LoadSkinImage();

	Beat::SkinImageMap LoadData(const std::string& fileName);
	void LoadData(const std::string& fileName, Beat::SkinImageMap& map);

private:
	const std::string directory = Skin::Directory;

	std::map<std::string, Beat::SkinImageType> imageName_;

	void CreateImageName();


	void SetImage(Beat::SkinImageMap& map, const std::filesystem::path& path, std::string&& fileName);

};

