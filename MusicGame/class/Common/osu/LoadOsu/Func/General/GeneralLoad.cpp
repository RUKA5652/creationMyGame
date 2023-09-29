#include "GeneralLoad.h"
#include<algorithm>
#include<sstream>
#include"GeneralLoadFunc.h"

namespace
{
	constexpr auto title("[General]");
}

GeneralLoad::GeneralLoad()
	: LoadSectionBase(title)
{
	Init();
}

GeneralLoad::~GeneralLoad()
{
}

bool GeneralLoad::LoadFile(const std::string& fileData, Beat::LoadDataPtr data)
{
	return LoadSectionBase::LoadFile(fileData, data->generalData);
}



void GeneralLoad::Init()
{
	setDataFuncVec_ =
	{
		std::bind_front(GeneralLoadFunc::AudioFilename()),
		std::bind_front(GeneralLoadFunc::AudioLeadIn()),
		std::bind_front(GeneralLoadFunc::Mode()),
		std::bind_front(GeneralLoadFunc::PreviewTime()),
		std::bind_front(GeneralLoadFunc::SampleSet()),
	};
}



