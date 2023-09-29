#pragma once
#include"../LoadSectionBase.h"
#include"../../../HitObj.h"

class HitObjLoad:
	public LoadSectionBase<HitObjVec>
{
public:
	HitObjLoad();

	bool LoadFile(const std::string& fileData, Beat::LoadDataPtr data) override;
private:

	void Init();

};

