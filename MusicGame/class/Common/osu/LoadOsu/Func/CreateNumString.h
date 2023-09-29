#pragma once
#include <optional>

struct CreateNumString
{
	std::optional<std::string> operator()(const std::string& data, const std::string& hed)
	{
		auto pos = data.find(hed);
		if (pos == data.npos)
		{
			return std::nullopt;
		}
		pos += hed.size();
		auto numString = data.substr(pos);
		return numString;
	}
};
