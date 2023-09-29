#pragma once
#include<vector>
#include<string>

inline namespace ScoreConstantData
{
	constexpr const char* FolderName = "resource/score";
	constexpr const char* Extension = "sco";
	constexpr int Max = 10;
}

struct HistoryScore
	:public  std::vector<int>
{
	HistoryScore();
	void set(int data);
};



