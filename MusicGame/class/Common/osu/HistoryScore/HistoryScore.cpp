#include "HistoryScore.h"
#include<algorithm>

HistoryScore::HistoryScore()
{
	this->reserve(Max);
}

void HistoryScore::set(int data)
{
	this->emplace_back(data);
	std::ranges::sort(*this, std::greater<int>{});
	auto result = std::ranges::unique(*this);
	this->erase(result.begin(), result.end());
	if (this->size() > Max)
	{
		this->erase(this->begin() + Max , this->end());
	}
}
