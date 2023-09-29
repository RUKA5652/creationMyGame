#pragma once
#include <string>
#include<fstream>


namespace
{
	constexpr auto extension = ".osu";
}

struct OpunOsuFile
{
	std::optional<std::string> operator()(const std::string& filePass)
	{
		auto num = filePass.find_last_of('.');
		if (num == filePass.npos)
		{
			return std::nullopt;
		}
		auto fileExtension = filePass.substr(num, filePass.size());
		if (fileExtension != extension)
		{
			return std::nullopt;
		}

		auto fileData = std::ifstream(filePass);
		std::istreambuf_iterator<char> it(fileData);
		std::istreambuf_iterator<char> last;
		std::string buff(it, last);
		return buff;
	}


};
