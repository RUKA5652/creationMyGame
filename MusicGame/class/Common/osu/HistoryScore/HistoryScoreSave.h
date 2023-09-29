#pragma once
#include <string>
#include "HistoryScore.h"
class HistoryScoreSave
{
public:
	bool Save(std::string musicFolderPath,const HistoryScore& data);

};

