#include "MetadataLoad.h"
#include<algorithm>
#include<sstream>
#include"MetadataLoadFunc.h"

namespace
{
	constexpr auto title("[Metadata]");
}

MetadataLoad::MetadataLoad()
	: LoadSectionBase(title)
{
	Init();
}

MetadataLoad::~MetadataLoad()
{
}

bool MetadataLoad::LoadFile(const std::string& fileData, Beat::LoadDataPtr data)
{
	return LoadSectionBase::LoadFile(fileData, data->metaData);
}


void MetadataLoad::Init()
{
	setDataFuncVec_ =
	{
		std::bind_front(MetadataLoadFunc::Artist()),
		std::bind_front(MetadataLoadFunc::Title()),
		std::bind_front(MetadataLoadFunc::Version()),
		std::bind_front(MetadataLoadFunc::Creator()),
	};
}
