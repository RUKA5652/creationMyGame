#pragma once
#include<string>
#include<filesystem>
#include<functional>
#include <regex>
/// <summary>
/// �t�H���_�T��
/// </summary>
class FolderSearch
{
public:
	FolderSearch(std::function<void(const std::filesystem::path&, std::string&&)>&& func);
	void operator()(const std::string& folder);
private:
	void Set(const std::filesystem::path& path);
	std::function<void(const std::filesystem::path&,std::string&&)> func_;
};
