#include "FolderSearch.h"

FolderSearch::FolderSearch(std::function<void(const std::filesystem::path&, std::string&&)>&& func)
{
	func_ = func;
}

void FolderSearch::operator()(const std::string& folder)
{
	for (auto& itr : std::filesystem::directory_iterator(folder.c_str()))
	{
		auto& path = itr.path();
		Set(path);
	}
}

void FolderSearch::Set(const std::filesystem::path& path)
{
	func_(path, path.stem().string());
}
