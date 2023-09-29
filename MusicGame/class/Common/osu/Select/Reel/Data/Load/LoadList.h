#pragma once
#include "../../ReelData.h"
#include "../../../../LoadOsu/LoadOsuFile.h"

class LoadList
{
public:


private:
	const char* musicListPath = "resource/musicList.list";
	Beat::ReelData* reelData_;
	std::unique_ptr<LoadOsuFile> load_;



};

