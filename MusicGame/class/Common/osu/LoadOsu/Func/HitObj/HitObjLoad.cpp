#include "HitObjLoad.h"
#include"HitObjLoadFunc.h"
#include<sstream>

namespace
{
	constexpr auto title("[HitObjects]");
}


HitObjLoad::HitObjLoad():
	LoadSectionBase(title)
{
	Init();
}

bool HitObjLoad::LoadFile(const std::string& fileData, Beat::LoadDataPtr data)
{
	return LoadSectionBase::LoadFile(fileData, data->hitObjVec.get());
}


void HitObjLoad::Init()
{
	setDataFuncVec_ =
	{
		HitObjLoadFunc::SetData(),
	};
}


