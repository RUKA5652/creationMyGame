#pragma once
#include"../LoadSectionBase.h"
#include <functional>
#include <optional>
#include<memory>
#include"../../../MetaData.h"
#include "../LoadFunc.h"


class MetadataLoad:
	public LoadSectionBase<Beat::MetaData>
{
public:
	MetadataLoad();
	~MetadataLoad();
	bool LoadFile(const std::string& fileData, Beat::LoadDataPtr data) override;
private:
	void Init();

};

